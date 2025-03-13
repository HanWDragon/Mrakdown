# 为什么要有协程，线程不香

## 进程

![](image/Pasted%20image%2020250306185158.png)

 ![](image/Pasted%20image%2020250306185344.png)
## 线程

![](image/Pasted%20image%2020250306185439.png)

![](image/Pasted%20image%2020250306185532.png)

![](image/Pasted%20image%2020250306193257.png)

![](image/Pasted%20image%2020250306193011.png)

![](image/Pasted%20image%2020250306193043.png)

### 存在的问题

![](image/Pasted%20image%2020250306193432.png)

## 协程

![](image/Pasted%20image%2020250306194240.png)

包含代码执行的状态，对于操作系统来说还是操作原来的线程，由 Go 的运行时来管理协程，让线程一直运行，没有上下文切换，只不过线程内运行不同的协程

![](image/Pasted%20image%2020250306193640.png)

![](image/Pasted%20image%2020250306193757.png)

![](image/Pasted%20image%2020250306193815.png)

![](image/Pasted%20image%2020250306193843.png)

![](image/Pasted%20image%2020250306193905.png)

### 优势

![](image/Pasted%20image%2020250306194307.png)

## 总结

![](image/Pasted%20image%2020250306194334.png)

# 协程的本质

## 协程的底层结构

![](image/Pasted%20image%2020250306200208.png)

![](image/Pasted%20image%2020250306200442.png)

想查看协程的定义在 runtime 包下的 runtime2.go 文件中的 g 结构体

```go
type g struct {
	// Stack parameters.
	// stack describes the actual stack memory: [stack.lo, stack.hi).
	// stackguard0 is the stack pointer compared in the Go stack growth prologue.
	// It is stack.lo+StackGuard normally, but can be StackPreempt to trigger a preemption.
	// stackguard1 is the stack pointer compared in the //go:systemstack stack growth prologue.
	// It is stack.lo+StackGuard on g0 and gsignal stacks.
	// It is ~0 on other goroutine stacks, to trigger a call to morestackc (and crash).
	stack       stack   // offset known to runtime/cgo
	stackguard0 uintptr // offset known to liblink
	stackguard1 uintptr // offset known to liblink

	_panic    *_panic // innermost panic - offset known to liblink
	_defer    *_defer // innermost defer
	m         *m      // current m; offset known to arm liblink
	sched     gobuf
	syscallsp uintptr // if status==Gsyscall, syscallsp = sched.sp to use during gc
	syscallpc uintptr // if status==Gsyscall, syscallpc = sched.pc to use during gc
	syscallbp uintptr // if status==Gsyscall, syscallbp = sched.bp to use in fpTraceback
	stktopsp  uintptr // expected sp at top of stack, to check in traceback
	// param is a generic pointer parameter field used to pass
	// values in particular contexts where other storage for the
	// parameter would be difficult to find. It is currently used
	// in four ways:
	// 1. When a channel operation wakes up a blocked goroutine, it sets param to
	//    point to the sudog of the completed blocking operation.
	// 2. By gcAssistAlloc1 to signal back to its caller that the goroutine completed
	//    the GC cycle. It is unsafe to do so in any other way, because the goroutine's
	//    stack may have moved in the meantime.
	// 3. By debugCallWrap to pass parameters to a new goroutine because allocating a
	//    closure in the runtime is forbidden.
	// 4. When a panic is recovered and control returns to the respective frame,
	//    param may point to a savedOpenDeferState.
	param        unsafe.Pointer
	atomicstatus atomic.Uint32
	stackLock    uint32 // sigprof/scang lock; TODO: fold in to atomicstatus
	goid         uint64
	schedlink    guintptr
	waitsince    int64      // approx time when the g become blocked
	waitreason   waitReason // if status==Gwaiting

	preempt       bool // preemption signal, duplicates stackguard0 = stackpreempt
	preemptStop   bool // transition to _Gpreempted on preemption; otherwise, just deschedule
	preemptShrink bool // shrink stack at synchronous safe point

	// asyncSafePoint is set if g is stopped at an asynchronous
	// safe point. This means there are frames on the stack
	// without precise pointer information.
	asyncSafePoint bool

	paniconfault bool // panic (instead of crash) on unexpected fault address
	gcscandone   bool // g has scanned stack; protected by _Gscan bit in status
	throwsplit   bool // must not split stack
	// activeStackChans indicates that there are unlocked channels
	// pointing into this goroutine's stack. If true, stack
	// copying needs to acquire channel locks to protect these
	// areas of the stack.
	activeStackChans bool
	// parkingOnChan indicates that the goroutine is about to
	// park on a chansend or chanrecv. Used to signal an unsafe point
	// for stack shrinking.
	parkingOnChan atomic.Bool
	// inMarkAssist indicates whether the goroutine is in mark assist.
	// Used by the execution tracer.
	inMarkAssist bool
	coroexit     bool // argument to coroswitch_m

	raceignore    int8  // ignore race detection events
	nocgocallback bool  // whether disable callback from C
	tracking      bool  // whether we're tracking this G for sched latency statistics
	trackingSeq   uint8 // used to decide whether to track this G
	trackingStamp int64 // timestamp of when the G last started being tracked
	runnableTime  int64 // the amount of time spent runnable, cleared when running, only used when tracking
	lockedm       muintptr
	fipsIndicator uint8
	sig           uint32
	writebuf      []byte
	sigcode0      uintptr
	sigcode1      uintptr
	sigpc         uintptr
	parentGoid    uint64          // goid of goroutine that created this goroutine
	gopc          uintptr         // pc of go statement that created this goroutine
	ancestors     *[]ancestorInfo // ancestor information goroutine(s) that created this goroutine (only used if debug.tracebackancestors)
	startpc       uintptr         // pc of goroutine function
	racectx       uintptr
	waiting       *sudog         // sudog structures this g is waiting on (that have a valid elem ptr); in lock order
	cgoCtxt       []uintptr      // cgo traceback context
	labels        unsafe.Pointer // profiler labels
	timer         *timer         // cached timer for time.Sleep
	sleepWhen     int64          // when to sleep until
	selectDone    atomic.Uint32  // are we participating in a select and did someone win the race?

	// goroutineProfiled indicates the status of this goroutine's stack for the
	// current in-progress goroutine profile
	goroutineProfiled goroutineProfileStateHolder

	coroarg   *coro // argument during coroutine transfers
	syncGroup *synctestGroup

	// Per-G tracer state.
	trace gTraceState

	// Per-G GC state

	// gcAssistBytes is this G's GC assist credit in terms of
	// bytes allocated. If this is positive, then the G has credit
	// to allocate gcAssistBytes bytes without assisting. If this
	// is negative, then the G must correct this by performing
	// scan work. We track this in bytes to make it fast to update
	// and check for debt in the malloc hot path. The assist ratio
	// determines how this corresponds to scan work debt.
	gcAssistBytes int64
}

type stack struct {
	lo uintptr
	hi uintptr
}

type gobuf struct {
	// The offsets of sp, pc, and g are known to (hard-coded in) libmach.
	//
	// ctxt is unusual with respect to GC: it may be a
	// heap-allocated funcval, so GC needs to track it, but it
	// needs to be set and cleared from assembly, where it's
	// difficult to have write barriers. However, ctxt is really a
	// saved, live register, and we only ever exchange it between
	// the real register and the gobuf. Hence, we treat it as a
	// root during stack scanning, which means assembly that saves
	// and restores it doesn't need write barriers. It's still
	// typed as a pointer so that any other writes from Go get
	// write barriers.
	sp   uintptr
	pc   uintptr
	g    guintptr
	ctxt unsafe.Pointer
	ret  uintptr
	lr   uintptr
	bp   uintptr // for framepointer-enabled architectures
}

```

## 对线程的抽象

![](image/Pasted%20image%2020250306201331.png)

对于线程的定义是在 runtime 包下的 runtime2.go 文件中的 m 结构体是描述操作系统线程需要的信息

```go
type m struct {
	g0      *g     // goroutine with scheduling stack
	morebuf gobuf  // gobuf arg to morestack
	divmod  uint32 // div/mod denominator for arm - known to liblink
	_       uint32 // align next field to 8 bytes

	// Fields not known to debuggers.
	procid          uint64            // for debuggers, but offset not hard-coded
	gsignal         *g                // signal-handling g
	goSigStack      gsignalStack      // Go-allocated signal handling stack
	sigmask         sigset            // storage for saved signal mask
	tls             [tlsSlots]uintptr // thread-local storage (for x86 extern register)
	mstartfn        func()
	curg            *g       // current running goroutine
	caughtsig       guintptr // goroutine running during fatal signal
	p               puintptr // attached p for executing go code (nil if not executing go code)
	nextp           puintptr
	oldp            puintptr // the p that was attached before executing a syscall
	id              int64
	mallocing       int32
	throwing        throwType
	preemptoff      string // if != "", keep curg running on this m
	locks           int32
	dying           int32
	profilehz       int32
	spinning        bool // m is out of work and is actively looking for work
	blocked         bool // m is blocked on a note
	newSigstack     bool // minit on C thread called sigaltstack
	printlock       int8
	incgo           bool          // m is executing a cgo call
	isextra         bool          // m is an extra m
	isExtraInC      bool          // m is an extra m that is not executing Go code
	isExtraInSig    bool          // m is an extra m in a signal handler
	freeWait        atomic.Uint32 // Whether it is safe to free g0 and delete m (one of freeMRef, freeMStack, freeMWait)
	needextram      bool
	g0StackAccurate bool // whether the g0 stack has accurate bounds
	traceback       uint8
	ncgocall        uint64        // number of cgo calls in total
	ncgo            int32         // number of cgo calls currently in progress
	cgoCallersUse   atomic.Uint32 // if non-zero, cgoCallers in use temporarily
	cgoCallers      *cgoCallers   // cgo traceback if crashing in cgo call
	park            note
	alllink         *m // on allm
	schedlink       muintptr
	lockedg         guintptr
	createstack     [32]uintptr // stack that created this thread, it's used for StackRecord.Stack0, so it must align with it.
	lockedExt       uint32      // tracking for external LockOSThread
	lockedInt       uint32      // tracking for internal lockOSThread
	mWaitList       mWaitList   // list of runtime lock waiters

	mLockProfile mLockProfile // fields relating to runtime.lock contention
	profStack    []uintptr    // used for memory/block/mutex stack traces

	// wait* are used to carry arguments from gopark into park_m, because
	// there's no stack to put them on. That is their sole purpose.
	waitunlockf          func(*g, unsafe.Pointer) bool
	waitlock             unsafe.Pointer
	waitTraceSkip        int
	waitTraceBlockReason traceBlockReason

	syscalltick uint32
	freelink    *m // on sched.freem
	trace       mTraceState

	// these are here because they are too large to be on the stack
	// of low-level NOSPLIT functions.
	libcall    libcall
	libcallpc  uintptr // for cpu profiler
	libcallsp  uintptr
	libcallg   guintptr
	winsyscall winlibcall // stores syscall parameters on windows

	vdsoSP uintptr // SP for traceback while in VDSO call (0 if not in call)
	vdsoPC uintptr // PC for traceback while in VDSO call

	// preemptGen counts the number of completed preemption
	// signals. This is used to detect when a preemption is
	// requested, but fails.
	preemptGen atomic.Uint32

	// Whether this is a pending preemption signal on this M.
	signalPending atomic.Uint32

	// pcvalue lookup cache
	pcvalueCache pcvalueCache

	dlogPerM

	mOS

	chacha8   chacha8rand.State
	cheaprand uint64

	// Up to 10 locks held by this m, maintained by the lock ranking code.
	locksHeldLen int
	locksHeld    [10]heldLockInfo

	// Size the runtime.m structure so it fits in the 2048-byte size class, and
	// not in the next-smallest (1792-byte) size class. That leaves the 11 low
	// bits of muintptr values available for flags, as required for
	// GOEXPERIMENT=spinbitmutex.
	_ [goexperiment.SpinbitMutexInt * 700 * (2 - goarch.PtrSize/4)]byte
}
```

其中 mos 针对每个操作系统不同的线程信息的封装

![](image/Pasted%20image%2020250306200952.png)

# 协程如何在线程上运行

## 单线程循环(Go 0.X)
 ![](image/Pasted%20image%2020250306201549.png)

schedule 方法在最后就调用 execute 方法

```go
// One round of scheduler: find a runnable goroutine and execute it.
// Never returns.
func schedule() {
	mp := getg().m

	if mp.locks != 0 {
		throw("schedule: holding locks")
	}

	if mp.lockedg != 0 {
		stoplockedm()
		execute(mp.lockedg.ptr(), false) // Never returns.
	}

	// We should not schedule away from a g that is executing a cgo call,
	// since the cgo call is using the m's g0 stack.
	if mp.incgo {
		throw("schedule: in cgo")
	}

top:
	pp := mp.p.ptr()
	pp.preempt = false

	// Safety check: if we are spinning, the run queue should be empty.
	// Check this before calling checkTimers, as that might call
	// goready to put a ready goroutine on the local run queue.
	if mp.spinning && (pp.runnext != 0 || pp.runqhead != pp.runqtail) {
		throw("schedule: spinning with local work")
	}

	gp, inheritTime, tryWakeP := findRunnable() // blocks until work is available

	if debug.dontfreezetheworld > 0 && freezing.Load() {
		// See comment in freezetheworld. We don't want to perturb
		// scheduler state, so we didn't gcstopm in findRunnable, but
		// also don't want to allow new goroutines to run.
		//
		// Deadlock here rather than in the findRunnable loop so if
		// findRunnable is stuck in a loop we don't perturb that
		// either.
		lock(&deadlock)
		lock(&deadlock)
	}

	// This thread is going to run a goroutine and is not spinning anymore,
	// so if it was marked as spinning we need to reset it now and potentially
	// start a new spinning M.
	if mp.spinning {
		resetspinning()
	}

	if sched.disable.user && !schedEnabled(gp) {
		// Scheduling of this goroutine is disabled. Put it on
		// the list of pending runnable goroutines for when we
		// re-enable user scheduling and look again.
		lock(&sched.lock)
		if schedEnabled(gp) {
			// Something re-enabled scheduling while we
			// were acquiring the lock.
			unlock(&sched.lock)
		} else {
			sched.disable.runnable.pushBack(gp)
			sched.disable.n++
			unlock(&sched.lock)
			goto top
		}
	}

	// If about to schedule a not-normal goroutine (a GCworker or tracereader),
	// wake a P if there is one.
	if tryWakeP {
		wakep()
	}
	if gp.lockedm != 0 {
		// Hands off own p to the locked m,
		// then blocks waiting for a new p.
		startlockedm(gp)
		goto top
	}

	execute(gp, inheritTime)
}
```

execute 方法

```go
// Schedules gp to run on the current M.
// If inheritTime is true, gp inherits the remaining time in the
// current time slice. Otherwise, it starts a new time slice.
// Never returns.
//
// Write barriers are allowed because this is called immediately after
// acquiring a P in several places.
//
//go:yeswritebarrierrec
func execute(gp *g, inheritTime bool) {
	mp := getg().m

	if goroutineProfile.active {
		// Make sure that gp has had its stack written out to the goroutine
		// profile, exactly as it was when the goroutine profiler first stopped
		// the world.
		tryRecordGoroutineProfile(gp, nil, osyield)
	}

	// Assign gp.m before entering _Grunning so running Gs have an
	// M.
	mp.curg = gp
	gp.m = mp
	casgstatus(gp, _Grunnable, _Grunning)
	gp.waitsince = 0
	gp.preempt = false
	gp.stackguard0 = gp.stack.lo + stackGuard
	if !inheritTime {
		mp.p.ptr().schedtick++
	}

	// Check whether the profiler needs to be turned on or off.
	hz := sched.profilehz
	if mp.profilehz != hz {
		setThreadCPUProfiler(hz)
	}

	trace := traceAcquire()
	if trace.ok() {
		trace.GoStart()
		traceRelease(trace)
	}

	gogo(&gp.sched)
}

```

gogo 方法，发现只有定义没有实现，估计底层是使用汇编代码，使用全局搜索找到在asm_xxx.s 文件里面，当我们 debug 中看到有个栈帧叫 goexit() ，这个并不是程序调用产生，而是手动创建的，然后执行用户书写的代码

这段汇编代码完成了以下工作

1. **从 `gobuf` 恢复协程状态**：这是一个核心操作，包括更新 SP（栈指针）、PC（程序计数器）等。
2. **设置当前 goroutine 的状态**：将 `gobuf_g` 中的 goroutine 结构设置到相关寄存器和 TLS。
3. **最终跳转到协程的执行位置**：完成真正的协程切换。

```go
func gogo(buf *gobuf)

// func gogo(buf *gobuf)  
// restore state from Gobuf; longjmp  
TEXT runtime·gogo(SB), NOSPLIT, $0-8  
    MOVQ   buf+0(FP), BX     // gobuf  
    MOVQ   gobuf_g(BX), DX  
    MOVQ   0(DX), CX     // make sure g != nil  
    JMP    gogo<>(SB)  
  
TEXT gogo<>(SB), NOSPLIT, $0  
    get_tls(CX)  
    MOVQ   DX, g(CX)  
    MOVQ   DX, R14       // set the g register  
    MOVQ   gobuf_sp(BX), SP   // restore SP  
    MOVQ   gobuf_ret(BX), AX  
    MOVQ   gobuf_ctxt(BX), DX  
    MOVQ   gobuf_bp(BX), BP  
    MOVQ   $0, gobuf_sp(BX)   // clear to help garbage collector  
    MOVQ   $0, gobuf_ret(BX)  
    MOVQ   $0, gobuf_ctxt(BX)  
    MOVQ   $0, gobuf_bp(BX)  
    MOVQ   gobuf_pc(BX), BX  
    JMP    BX
```

goexit 方法

```go
// goexit is the return stub at the top of every goroutine call stack.
// Each goroutine stack is constructed as if goexit called the
// goroutine's entry point function, so that when the entry point
// function returns, it will return to goexit, which will call goexit1
// to perform the actual exit.
//
// This function must never be called directly. Call goexit1 instead.
// gentraceback assumes that goexit terminates the stack. A direct
// call on the stack will cause gentraceback to stop walking the stack
// prematurely and if there is leftover state it may panic.
func goexit(neverCallThisFunction)

// The top-most function running on a goroutine
// returns to goexit+PCQuantum.
TEXT runtime·goexit(SB),NOSPLIT|TOPFRAME|NOFRAME,$0-0
	BYTE	$0x90	// NOP
	CALL	runtime·goexit1(SB)	// does not return
	// traceback from goexit1 must hit code range of goexit
	BYTE	$0x90	// NOP

// Finishes execution of the current goroutine.
func goexit1() {
	if raceenabled {
		if gp := getg(); gp.syncGroup != nil {
			racereleasemergeg(gp, gp.syncGroup.raceaddr())
		}
		racegoend()
	}
	trace := traceAcquire()
	if trace.ok() {
		trace.GoEnd()
		traceRelease(trace)
	}
	mcall(goexit0)
}

// goexit continuation on g0.  
func goexit0(gp *g) {  
    gdestroy(gp)  
    schedule()  
}

// mcall switches from the g to the g0 stack and invokes fn(g),
// where g is the goroutine that made the call.
// mcall saves g's current PC/SP in g->sched so that it can be restored later.
// It is up to fn to arrange for that later execution, typically by recording
// g in a data structure, causing something to call ready(g) later.
// mcall returns to the original goroutine g later, when g has been rescheduled.
// fn must not return at all; typically it ends by calling schedule, to let the m
// run other goroutines.
//
// mcall can only be called from g stacks (not g0, not gsignal).
//
// This must NOT be go:noescape: if fn is a stack-allocated closure,
// fn puts g on a run queue, and g executes before fn returns, the
// closure will be invalidated while it is still executing.
func mcall(fn func(*g))
```

## 多线程循环(Go 1.X)

![](image/Pasted%20image%2020250306210057.png)

![](image/Pasted%20image%2020250306210147.png)

## 线程循环

![](image/Pasted%20image%2020250306210249.png)

## 问题

![](image/Pasted%20image%2020250306210344.png)

## 总结

![](image/Pasted%20image%2020250306210406.png)

# GMP 调度模型

## 上文循环模型存在的问题

这个模型解决的是第二个问题，进行并发时锁的冲突和等待

![](image/Pasted%20image%2020250306210549.png)

## 多线程循环

- 每次抓取一个，会产生竞争问题，需要加锁

![](image/Pasted%20image%2020250308140449.png)

## 本地队列

我们需要在 M 抓取协程时尽量无锁，于是使用本地队列，每次存一堆，用完再取，因为整个模型叫作 GMP 模型，G 和 M 都在之前介绍了，就只剩下 P 了，这个也是 Go 底层取的名字，在 runtime 包下 runtime2.go 文件里的 P 结构

![](image/Pasted%20image%2020250308141003.png)

## P 结构体

![](image/Pasted%20image%2020250308143420.png)

```go
type p struct {
	id          int32
	status      uint32 // one of pidle/prunning/...
	link        puintptr
	schedtick   uint32     // incremented on every scheduler call
	syscalltick uint32     // incremented on every system call
	sysmontick  sysmontick // last tick observed by sysmon
	m           muintptr   // back-link to associated m (nil if idle)
	mcache      *mcache
	pcache      pageCache
	raceprocctx uintptr

	deferpool    []*_defer // pool of available defer structs (see panic.go)
	deferpoolbuf [32]*_defer

	// Cache of goroutine ids, amortizes accesses to runtime·sched.goidgen.
	goidcache    uint64
	goidcacheend uint64

	// Queue of runnable goroutines. Accessed without lock.
	runqhead uint32 // 队列头指针
	runqtail uint32 // 队列尾指针
	runq     [256]guintptr // 队列指针
	// runnext, if non-nil, is a runnable G that was ready'd by
	// the current G and should be run next instead of what's in
	// runq if there's time remaining in the running G's time
	// slice. It will inherit the time left in the current time
	// slice. If a set of goroutines is locked in a
	// communicate-and-wait pattern, this schedules that set as a
	// unit and eliminates the (potentially large) scheduling
	// latency that otherwise arises from adding the ready'd
	// goroutines to the end of the run queue.
	//
	// Note that while other P's may atomically CAS this to zero,
	// only the owner P can CAS it to a valid G.
	runnext guintptr // 下一个可用的指针

	// Available G's (status == Gdead)
	gFree struct {
		gList
		n int32
	}

	sudogcache []*sudog
	sudogbuf   [128]*sudog

	// Cache of mspan objects from the heap.
	mspancache struct {
		// We need an explicit length here because this field is used
		// in allocation codepaths where write barriers are not allowed,
		// and eliminating the write barrier/keeping it eliminated from
		// slice updates is tricky, more so than just managing the length
		// ourselves.
		len int
		buf [128]*mspan
	}

	// Cache of a single pinner object to reduce allocations from repeated
	// pinner creation.
	pinnerCache *pinner

	trace pTraceState

	palloc persistentAlloc // per-P to avoid mutex

	// Per-P GC state
	gcAssistTime         int64 // Nanoseconds in assistAlloc
	gcFractionalMarkTime int64 // Nanoseconds in fractional mark worker (atomic)

	// limiterEvent tracks events for the GC CPU limiter.
	limiterEvent limiterEvent

	// gcMarkWorkerMode is the mode for the next mark worker to run in.
	// That is, this is used to communicate with the worker goroutine
	// selected for immediate execution by
	// gcController.findRunnableGCWorker. When scheduling other goroutines,
	// this field must be set to gcMarkWorkerNotWorker.
	gcMarkWorkerMode gcMarkWorkerMode
	// gcMarkWorkerStartTime is the nanotime() at which the most recent
	// mark worker started.
	gcMarkWorkerStartTime int64

	// gcw is this P's GC work buffer cache. The work buffer is
	// filled by write barriers, drained by mutator assists, and
	// disposed on certain GC state transitions.
	gcw gcWork

	// wbBuf is this P's GC write barrier buffer.
	//
	// TODO: Consider caching this in the running G.
	wbBuf wbBuf

	runSafePointFn uint32 // if 1, run sched.safePointFn at next safe point

	// statsSeq is a counter indicating whether this P is currently
	// writing any stats. Its value is even when not, odd when it is.
	statsSeq atomic.Uint32

	// Timer heap.
	timers timers

	// maxStackScanDelta accumulates the amount of stack space held by
	// live goroutines (i.e. those eligible for stack scanning).
	// Flushed to gcController.maxStackScan once maxStackScanSlack
	// or -maxStackScanSlack is reached.
	maxStackScanDelta int64

	// gc-time statistics about current goroutines
	// Note that this differs from maxStackScan in that this
	// accumulates the actual stack observed to be used at GC time (hi - sp),
	// not an instantaneous measure of the total stack size that might need
	// to be scanned (hi - lo).
	scannedStackSize uint64 // stack size of goroutines scanned by this P
	scannedStacks    uint64 // number of goroutines scanned by this P

	// preempt is set to indicate that this P should be enter the
	// scheduler ASAP (regardless of what G is running on it).
	preempt bool

	// gcStopTime is the nanotime timestamp that this P last entered _Pgcstop.
	gcStopTime int64

	// Padding is no longer needed. False sharing is now not a worry because p is large enough
	// that its size class is an integer multiple of the cache line size (for any of our architectures).
}
```

## GMP 模型

![](image/Pasted%20image%2020250308180134.png)

![](image/Pasted%20image%2020250308180214.png)

## P 的作用

![](image/Pasted%20image%2020250308180253.png)

这里就要回到上文中介绍的[协程运行流程](#协程如何在线程上运行)，主要的流程都是在 proc.go 文件里，首先看 schedule 这个是线程循环的第一个方法，我们需要关注如何获取协程，主要逻辑是 findRunnable 方法

### findRunnable

```go
gp, inheritTime, tryWakeP := findRunnable() // blocks until work is available

func findRunnable() (gp *g, inheritTime, tryWakeP bool) {
	// 获得线程 m 结构体
	mp := getg().m

	// The conditions here and in handoffp must agree: if
	// findrunnable would return a G to run, handoffp must start
	// an M.

top:
	// 拿到 P 结构体指针
	pp := mp.p.ptr()
	if sched.gcwaiting.Load() {
		gcstopm()
		goto top
	}
	if pp.runSafePointFn != 0 {
		runSafePointFn()
	}

	// now and pollUntil are saved for work stealing later,
	// which may steal timers. It's important that between now
	// and then, nothing blocks, so these numbers remain mostly
	// relevant.
	now, pollUntil, _ := pp.timers.check(0)

	// Try to schedule the trace reader.
	if traceEnabled() || traceShuttingDown() {
		gp := traceReader()
		if gp != nil {
			trace := traceAcquire()
			casgstatus(gp, _Gwaiting, _Grunnable)
			if trace.ok() {
				trace.GoUnpark(gp, 0)
				traceRelease(trace)
			}
			return gp, false, true
		}
	}

	// Try to schedule a GC worker.
	if gcBlackenEnabled != 0 {
		gp, tnow := gcController.findRunnableGCWorker(pp, now)
		if gp != nil {
			return gp, false, true
		}
		now = tnow
	}

	// Check the global runnable queue once in a while to ensure fairness.
	// Otherwise two goroutines can completely occupy the local runqueue
	// by constantly respawning each other.
	if pp.schedtick%61 == 0 && sched.runqsize > 0 {
		lock(&sched.lock)
		gp := globrunqget(pp, 1)
		unlock(&sched.lock)
		if gp != nil {
			return gp, false, false
		}
	}

	// Wake up the finalizer G.
	if fingStatus.Load()&(fingWait|fingWake) == fingWait|fingWake {
		if gp := wakefing(); gp != nil {
			ready(gp, 0, true)
		}
	}
	if *cgo_yield != nil {
		asmcgocall(*cgo_yield, nil)
	}

	// local runq
	// 这里就是从本地队列中获取
	if gp, inheritTime := runqget(pp); gp != nil {
		return gp, inheritTime, false
	}

	// global runq
	if sched.runqsize != 0 {
		lock(&sched.lock)
		gp := globrunqget(pp, 0)
		unlock(&sched.lock)
		if gp != nil {
			return gp, false, false
		}
	}

	// Poll network.
	// This netpoll is only an optimization before we resort to stealing.
	// We can safely skip it if there are no waiters or a thread is blocked
	// in netpoll already. If there is any kind of logical race with that
	// blocked thread (e.g. it has already returned from netpoll, but does
	// not set lastpoll yet), this thread will do blocking netpoll below
	// anyway.
	if netpollinited() && netpollAnyWaiters() && sched.lastpoll.Load() != 0 {
		if list, delta := netpoll(0); !list.empty() { // non-blocking
			gp := list.pop()
			injectglist(&list)
			netpollAdjustWaiters(delta)
			trace := traceAcquire()
			casgstatus(gp, _Gwaiting, _Grunnable)
			if trace.ok() {
				trace.GoUnpark(gp, 0)
				traceRelease(trace)
			}
			return gp, false, false
		}
	}

	// Spinning Ms: steal work from other Ps.
	//
	// Limit the number of spinning Ms to half the number of busy Ps.
	// This is necessary to prevent excessive CPU consumption when
	// GOMAXPROCS>>1 but the program parallelism is low.
	if mp.spinning || 2*sched.nmspinning.Load() < gomaxprocs-sched.npidle.Load() {
		if !mp.spinning {
			mp.becomeSpinning()
		}

		gp, inheritTime, tnow, w, newWork := stealWork(now)
		if gp != nil {
			// Successfully stole.
			return gp, inheritTime, false
		}
		if newWork {
			// There may be new timer or GC work; restart to
			// discover.
			goto top
		}

		now = tnow
		if w != 0 && (pollUntil == 0 || w < pollUntil) {
			// Earlier timer to wait for.
			pollUntil = w
		}
	}

	// We have nothing to do.
	//
	// If we're in the GC mark phase, can safely scan and blacken objects,
	// and have work to do, run idle-time marking rather than give up the P.
	if gcBlackenEnabled != 0 && gcMarkWorkAvailable(pp) && gcController.addIdleMarkWorker() {
		node := (*gcBgMarkWorkerNode)(gcBgMarkWorkerPool.pop())
		if node != nil {
			pp.gcMarkWorkerMode = gcMarkWorkerIdleMode
			gp := node.gp.ptr()

			trace := traceAcquire()
			casgstatus(gp, _Gwaiting, _Grunnable)
			if trace.ok() {
				trace.GoUnpark(gp, 0)
				traceRelease(trace)
			}
			return gp, false, false
		}
		gcController.removeIdleMarkWorker()
	}

	// wasm only:
	// If a callback returned and no other goroutine is awake,
	// then wake event handler goroutine which pauses execution
	// until a callback was triggered.
	gp, otherReady := beforeIdle(now, pollUntil)
	if gp != nil {
		trace := traceAcquire()
		casgstatus(gp, _Gwaiting, _Grunnable)
		if trace.ok() {
			trace.GoUnpark(gp, 0)
			traceRelease(trace)
		}
		return gp, false, false
	}
	if otherReady {
		goto top
	}

	// Before we drop our P, make a snapshot of the allp slice,
	// which can change underfoot once we no longer block
	// safe-points. We don't need to snapshot the contents because
	// everything up to cap(allp) is immutable.
	allpSnapshot := allp
	// Also snapshot masks. Value changes are OK, but we can't allow
	// len to change out from under us.
	idlepMaskSnapshot := idlepMask
	timerpMaskSnapshot := timerpMask

	// return P and block
	lock(&sched.lock)
	if sched.gcwaiting.Load() || pp.runSafePointFn != 0 {
		unlock(&sched.lock)
		goto top
	}
	if sched.runqsize != 0 {
		gp := globrunqget(pp, 0)
		unlock(&sched.lock)
		return gp, false, false
	}
	if !mp.spinning && sched.needspinning.Load() == 1 {
		// See "Delicate dance" comment below.
		mp.becomeSpinning()
		unlock(&sched.lock)
		goto top
	}
	if releasep() != pp {
		throw("findrunnable: wrong p")
	}
	now = pidleput(pp, now)
	unlock(&sched.lock)

	// Delicate dance: thread transitions from spinning to non-spinning
	// state, potentially concurrently with submission of new work. We must
	// drop nmspinning first and then check all sources again (with
	// #StoreLoad memory barrier in between). If we do it the other way
	// around, another thread can submit work after we've checked all
	// sources but before we drop nmspinning; as a result nobody will
	// unpark a thread to run the work.
	//
	// This applies to the following sources of work:
	//
	// * Goroutines added to the global or a per-P run queue.
	// * New/modified-earlier timers on a per-P timer heap.
	// * Idle-priority GC work (barring golang.org/issue/19112).
	//
	// If we discover new work below, we need to restore m.spinning as a
	// signal for resetspinning to unpark a new worker thread (because
	// there can be more than one starving goroutine).
	//
	// However, if after discovering new work we also observe no idle Ps
	// (either here or in resetspinning), we have a problem. We may be
	// racing with a non-spinning M in the block above, having found no
	// work and preparing to release its P and park. Allowing that P to go
	// idle will result in loss of work conservation (idle P while there is
	// runnable work). This could result in complete deadlock in the
	// unlikely event that we discover new work (from netpoll) right as we
	// are racing with _all_ other Ps going idle.
	//
	// We use sched.needspinning to synchronize with non-spinning Ms going
	// idle. If needspinning is set when they are about to drop their P,
	// they abort the drop and instead become a new spinning M on our
	// behalf. If we are not racing and the system is truly fully loaded
	// then no spinning threads are required, and the next thread to
	// naturally become spinning will clear the flag.
	//
	// Also see "Worker thread parking/unparking" comment at the top of the
	// file.
	wasSpinning := mp.spinning
	if mp.spinning {
		mp.spinning = false
		if sched.nmspinning.Add(-1) < 0 {
			throw("findrunnable: negative nmspinning")
		}

		// Note the for correctness, only the last M transitioning from
		// spinning to non-spinning must perform these rechecks to
		// ensure no missed work. However, the runtime has some cases
		// of transient increments of nmspinning that are decremented
		// without going through this path, so we must be conservative
		// and perform the check on all spinning Ms.
		//
		// See https://go.dev/issue/43997.

		// Check global and P runqueues again.

		lock(&sched.lock)
		if sched.runqsize != 0 {
			pp, _ := pidlegetSpinning(0)
			if pp != nil {
				gp := globrunqget(pp, 0)
				if gp == nil {
					throw("global runq empty with non-zero runqsize")
				}
				unlock(&sched.lock)
				acquirep(pp)
				mp.becomeSpinning()
				return gp, false, false
			}
		}
		unlock(&sched.lock)

		pp := checkRunqsNoP(allpSnapshot, idlepMaskSnapshot)
		if pp != nil {
			acquirep(pp)
			mp.becomeSpinning()
			goto top
		}

		// Check for idle-priority GC work again.
		pp, gp := checkIdleGCNoP()
		if pp != nil {
			acquirep(pp)
			mp.becomeSpinning()

			// Run the idle worker.
			pp.gcMarkWorkerMode = gcMarkWorkerIdleMode
			trace := traceAcquire()
			casgstatus(gp, _Gwaiting, _Grunnable)
			if trace.ok() {
				trace.GoUnpark(gp, 0)
				traceRelease(trace)
			}
			return gp, false, false
		}

		// Finally, check for timer creation or expiry concurrently with
		// transitioning from spinning to non-spinning.
		//
		// Note that we cannot use checkTimers here because it calls
		// adjusttimers which may need to allocate memory, and that isn't
		// allowed when we don't have an active P.
		pollUntil = checkTimersNoP(allpSnapshot, timerpMaskSnapshot, pollUntil)
	}

	// Poll network until next timer.
	if netpollinited() && (netpollAnyWaiters() || pollUntil != 0) && sched.lastpoll.Swap(0) != 0 {
		sched.pollUntil.Store(pollUntil)
		if mp.p != 0 {
			throw("findrunnable: netpoll with p")
		}
		if mp.spinning {
			throw("findrunnable: netpoll with spinning")
		}
		delay := int64(-1)
		if pollUntil != 0 {
			if now == 0 {
				now = nanotime()
			}
			delay = pollUntil - now
			if delay < 0 {
				delay = 0
			}
		}
		if faketime != 0 {
			// When using fake time, just poll.
			delay = 0
		}
		list, delta := netpoll(delay) // block until new work is available
		// Refresh now again, after potentially blocking.
		now = nanotime()
		sched.pollUntil.Store(0)
		sched.lastpoll.Store(now)
		if faketime != 0 && list.empty() {
			// Using fake time and nothing is ready; stop M.
			// When all M's stop, checkdead will call timejump.
			stopm()
			goto top
		}
		lock(&sched.lock)
		pp, _ := pidleget(now)
		unlock(&sched.lock)
		if pp == nil {
			injectglist(&list)
			netpollAdjustWaiters(delta)
		} else {
			acquirep(pp)
			if !list.empty() {
				gp := list.pop()
				injectglist(&list)
				netpollAdjustWaiters(delta)
				trace := traceAcquire()
				casgstatus(gp, _Gwaiting, _Grunnable)
				if trace.ok() {
					trace.GoUnpark(gp, 0)
					traceRelease(trace)
				}
				return gp, false, false
			}
			if wasSpinning {
				mp.becomeSpinning()
			}
			goto top
		}
	} else if pollUntil != 0 && netpollinited() {
		pollerPollUntil := sched.pollUntil.Load()
		if pollerPollUntil == 0 || pollerPollUntil > pollUntil {
			netpollBreak()
		}
	}
	stopm()
	goto top
} 
```

### runqget

这个就是在本地运行队列中获取可用的 g，

```go

// Get g from local runnable queue.
// If inheritTime is true, gp should inherit the remaining time in the
// current time slice. Otherwise, it should start a new time slice.
// Executed only by the owner P.
func runqget(pp *p) (gp *g, inheritTime bool) {
	// If there's a runnext, it's the next G to run.
	next := pp.runnext
	// If the runnext is non-0 and the CAS fails, it could only have been stolen by another P,
	// because other Ps can race to set runnext to 0, but only the current P can set it to non-0.
	// Hence, there's no need to retry this CAS if it fails.
	if next != 0 && pp.runnext.cas(next, 0) {
		return next.ptr(), true
	}

	for {
		h := atomic.LoadAcq(&pp.runqhead) // load-acquire, synchronize with other consumers
		t := pp.runqtail
		if t == h {
			return nil, false
		}
		gp := pp.runq[h%uint32(len(pp.runq))].ptr()
		if atomic.CasRel(&pp.runqhead, h, h+1) { // cas-release, commits consume
			return gp, false
		}
	}
}
```

### globrunqget

```go
// Try get a batch of G's from the global runnable queue.  
// sched.lock must be held.  
func globrunqget(pp *p, max int32) *g {  
    assertLockHeld(&sched.lock)  
  
    if sched.runqsize == 0 {  
       return nil  
    }  
  
    n := sched.runqsize/gomaxprocs + 1  
    if n > sched.runqsize {  
       n = sched.runqsize  
    }  
    if max > 0 && n > max {  
       n = max  
    }  
    if n > int32(len(pp.runq))/2 {  
       n = int32(len(pp.runq)) / 2  
    }  
  
    sched.runqsize -= n  
  
    gp := sched.runq.pop()  
    n--  
    for ; n > 0; n-- {  
       gp1 := sched.runq.pop()  
       runqput(pp, gp1, false)  
    }  
    return gp  
}
```

### stealWork

```go
// stealWork attempts to steal a runnable goroutine or timer from any P.
//
// If newWork is true, new work may have been readied.
//
// If now is not 0 it is the current time. stealWork returns the passed time or
// the current time if now was passed as 0.
func stealWork(now int64) (gp *g, inheritTime bool, rnow, pollUntil int64, newWork bool) {
	pp := getg().m.p.ptr()

	ranTimer := false

	const stealTries = 4
	for i := 0; i < stealTries; i++ {
		stealTimersOrRunNextG := i == stealTries-1

		for enum := stealOrder.start(cheaprand()); !enum.done(); enum.next() {
			if sched.gcwaiting.Load() {
				// GC work may be available.
				return nil, false, now, pollUntil, true
			}
			p2 := allp[enum.position()]
			if pp == p2 {
				continue
			}

			// Steal timers from p2. This call to checkTimers is the only place
			// where we might hold a lock on a different P's timers. We do this
			// once on the last pass before checking runnext because stealing
			// from the other P's runnext should be the last resort, so if there
			// are timers to steal do that first.
			//
			// We only check timers on one of the stealing iterations because
			// the time stored in now doesn't change in this loop and checking
			// the timers for each P more than once with the same value of now
			// is probably a waste of time.
			//
			// timerpMask tells us whether the P may have timers at all. If it
			// can't, no need to check at all.
			if stealTimersOrRunNextG && timerpMask.read(enum.position()) {
				tnow, w, ran := p2.timers.check(now)
				now = tnow
				if w != 0 && (pollUntil == 0 || w < pollUntil) {
					pollUntil = w
				}
				if ran {
					// Running the timers may have
					// made an arbitrary number of G's
					// ready and added them to this P's
					// local run queue. That invalidates
					// the assumption of runqsteal
					// that it always has room to add
					// stolen G's. So check now if there
					// is a local G to run.
					if gp, inheritTime := runqget(pp); gp != nil {
						return gp, inheritTime, now, pollUntil, ranTimer
					}
					ranTimer = true
				}
			}

			// Don't bother to attempt to steal if p2 is idle.
			if !idlepMask.read(enum.position()) {
				if gp := runqsteal(pp, p2, stealTimersOrRunNextG); gp != nil {
					return gp, false, now, pollUntil, ranTimer
				}
			}
		}
	}

	// No goroutines found to steal. Regardless, running a timer may have
	// made some goroutine ready that we missed. Indicate the next timer to
	// wait for.
	return nil, false, now, pollUntil, ranTimer
}

```

## 任务窃取

![](image/Pasted%20image%2020250310190013.png)

![](image/Pasted%20image%2020250310190028.png)

### 偷取机制

![](image/Pasted%20image%2020250310190125.png)

## 新建协程

![](image/Pasted%20image%2020250310190303.png)

在 runtime 包下 proc.go 文件中的 newproc 方法

```go
// Create a new g running fn.
// Put it on the queue of g's waiting to run.
// The compiler turns a go statement into a call to this.
func newproc(fn *funcval) {
	gp := getg()
	pc := sys.GetCallerPC()
	systemstack(func() {
		newg := newproc1(fn, gp, pc, false, waitReasonZero)

		pp := getg().m.p.ptr()
		runqput(pp, newg, true)

		if mainStarted {
			wakep()
		}
	})
}

// Create a new g in state _Grunnable (or _Gwaiting if parked is true), starting at fn.
// callerpc is the address of the go statement that created this. The caller is responsible
// for adding the new g to the scheduler. If parked is true, waitreason must be non-zero.
func newproc1(fn *funcval, callergp *g, callerpc uintptr, parked bool, waitreason waitReason) *g {
	if fn == nil {
		fatal("go of nil func value")
	}

	mp := acquirem() // disable preemption because we hold M and P in local vars.
	pp := mp.p.ptr()
	newg := gfget(pp)
	if newg == nil {
		newg = malg(stackMin)
		casgstatus(newg, _Gidle, _Gdead)
		allgadd(newg) // publishes with a g->status of Gdead so GC scanner doesn't look at uninitialized stack.
	}
	if newg.stack.hi == 0 {
		throw("newproc1: newg missing stack")
	}

	if readgstatus(newg) != _Gdead {
		throw("newproc1: new g is not Gdead")
	}

	totalSize := uintptr(4*goarch.PtrSize + sys.MinFrameSize) // extra space in case of reads slightly beyond frame
	totalSize = alignUp(totalSize, sys.StackAlign)
	sp := newg.stack.hi - totalSize
	if usesLR {
		// caller's LR
		*(*uintptr)(unsafe.Pointer(sp)) = 0
		prepGoExitFrame(sp)
	}
	if GOARCH == "arm64" {
		// caller's FP
		*(*uintptr)(unsafe.Pointer(sp - goarch.PtrSize)) = 0
	}

	memclrNoHeapPointers(unsafe.Pointer(&newg.sched), unsafe.Sizeof(newg.sched))
	newg.sched.sp = sp
	newg.stktopsp = sp
	newg.sched.pc = abi.FuncPCABI0(goexit) + sys.PCQuantum // +PCQuantum so that previous instruction is in same function
	newg.sched.g = guintptr(unsafe.Pointer(newg))
	gostartcallfn(&newg.sched, fn)
	newg.parentGoid = callergp.goid
	newg.gopc = callerpc
	newg.ancestors = saveAncestors(callergp)
	newg.startpc = fn.fn
	if isSystemGoroutine(newg, false) {
		sched.ngsys.Add(1)
	} else {
		// Only user goroutines inherit synctest groups and pprof labels.
		newg.syncGroup = callergp.syncGroup
		if mp.curg != nil {
			newg.labels = mp.curg.labels
		}
		if goroutineProfile.active {
			// A concurrent goroutine profile is running. It should include
			// exactly the set of goroutines that were alive when the goroutine
			// profiler first stopped the world. That does not include newg, so
			// mark it as not needing a profile before transitioning it from
			// _Gdead.
			newg.goroutineProfiled.Store(goroutineProfileSatisfied)
		}
	}
	// Track initial transition?
	newg.trackingSeq = uint8(cheaprand())
	if newg.trackingSeq%gTrackingPeriod == 0 {
		newg.tracking = true
	}
	gcController.addScannableStack(pp, int64(newg.stack.hi-newg.stack.lo))

	// Get a goid and switch to runnable. Make all this atomic to the tracer.
	trace := traceAcquire()
	var status uint32 = _Grunnable
	if parked {
		status = _Gwaiting
		newg.waitreason = waitreason
	}
	if pp.goidcache == pp.goidcacheend {
		// Sched.goidgen is the last allocated id,
		// this batch must be [sched.goidgen+1, sched.goidgen+GoidCacheBatch].
		// At startup sched.goidgen=0, so main goroutine receives goid=1.
		pp.goidcache = sched.goidgen.Add(_GoidCacheBatch)
		pp.goidcache -= _GoidCacheBatch - 1
		pp.goidcacheend = pp.goidcache + _GoidCacheBatch
	}
	newg.goid = pp.goidcache
	casgstatus(newg, _Gdead, status)
	pp.goidcache++
	newg.trace.reset()
	if trace.ok() {
		trace.GoCreate(newg, newg.startpc, parked)
		traceRelease(trace)
	}

	// Set up race context.
	if raceenabled {
		newg.racectx = racegostart(callerpc)
		newg.raceignore = 0
		if newg.labels != nil {
			// See note in proflabel.go on labelSync's role in synchronizing
			// with the reads in the signal handler.
			racereleasemergeg(newg, unsafe.Pointer(&labelSync))
		}
	}
	releasem(mp)

	return newg
}
```

## 问题

解决了第二个问题，现在还剩第一个问题，通过本地队列避免了总是竞争全局独占锁，现在就是如何实现线程上协程的鬓发

![](image/Pasted%20image%2020250310190655.png)

# 如何实现协程并发

## 问题

上文通过 GMP 调度模型解决了第二个问题，现在还有第一个问题

![](image/Pasted%20image%2020250310190927.png)

## 协程饥饿问题

有两个耗时协程，假如耗时，将线程占住了，后面很多时间敏感任务就会失败

![](image/Pasted%20image%2020250310191124.png)

### 全局队列饥饿

如果时间过长后中断保存放入本地队列，会导致本地队列一直循环，导致在全局队列中的任务得不到执行

![](image/Pasted%20image%2020250310192013.png)

解决方法就是每隔一段时间或者其他条件，从全局任务队列中获取一些任务，参与到小循环

![](image/Pasted%20image%2020250310192420.png)

## 线程循环

![](image/Pasted%20image%2020250310191338.png)

### 触发切换

![](image/Pasted%20image%2020250310191516.png)

主要是在 runtime 包下 proc.go 文件的 findRunnable 方法

```go
// Check the global runnable queue once in a while to ensure fairness.  
// Otherwise two goroutines can completely occupy the local runqueue  
// by constantly respawning each other.  
if pp.schedtick%61 == 0 && sched.runqsize > 0 {  
    lock(&sched.lock)  
    gp := globrunqget(pp, 1)  
    unlock(&sched.lock)  
    if gp != nil {  
       return gp, false, false  
    }  
}
```

### 切换时机

![](image/Pasted%20image%2020250310193753.png)

#### 主动挂起（runtime.gopark）

很多提供的 API 底层都使用了这个，不过这个方法是小写开头，用户无法调用，但是可以使用 Sleep 来间接的使用，还有一个问题是，调用之后就进入等待排队状态，满足条件才可以运行

![](image/Pasted%20image%2020250310202515.png)

```go
// Puts the current goroutine into a waiting state and calls unlockf on the
// system stack.
//
// If unlockf returns false, the goroutine is resumed.
//
// unlockf must not access this G's stack, as it may be moved between
// the call to gopark and the call to unlockf.
//
// Note that because unlockf is called after putting the G into a waiting
// state, the G may have already been readied by the time unlockf is called
// unless there is external synchronization preventing the G from being
// readied. If unlockf returns false, it must guarantee that the G cannot be
// externally readied.
//
// Reason explains why the goroutine has been parked. It is displayed in stack
// traces and heap dumps. Reasons should be unique and descriptive. Do not
// re-use reasons, add new ones.
//
// gopark should be an internal detail,
// but widely used packages access it using linkname.
// Notable members of the hall of shame include:
//   - gvisor.dev/gvisor
//   - github.com/sagernet/gvisor
//
// Do not remove or change the type signature.
// See go.dev/issue/67401.
//
//go:linkname gopark
func gopark(unlockf func(*g, unsafe.Pointer) bool, lock unsafe.Pointer, reason waitReason, traceReason traceBlockReason, traceskip int) {
	if reason != waitReasonSleep {
		checkTimeouts() // timeouts may expire while two goroutines keep the scheduler busy
	}
	mp := acquirem()
	gp := mp.curg
	status := readgstatus(gp)
	if status != _Grunning && status != _Gscanrunning {
		throw("gopark: bad g status")
	}
	mp.waitlock = lock
	mp.waitunlockf = unlockf
	gp.waitreason = reason
	mp.waitTraceBlockReason = traceReason
	mp.waitTraceSkip = traceskip
	releasem(mp)
	// can't do anything that might move the G between Ms here.
	// 从 g 到 g0
	mcall(park_m)
}
```

#### 系统调用完成时

![](image/Pasted%20image%2020250310203716.png)

```go
// The goroutine g exited its system call.
// Arrange for it to run on a cpu again.
// This is called only from the go syscall library, not
// from the low-level system calls used by the runtime.
//
// Write barriers are not allowed because our P may have been stolen.
//
// This is exported via linkname to assembly in the syscall package.
//
// exitsyscall should be an internal detail,
// but widely used packages access it using linkname.
// Notable members of the hall of shame include:
//   - gvisor.dev/gvisor
//
// Do not remove or change the type signature.
// See go.dev/issue/67401.
//
//go:nosplit
//go:nowritebarrierrec
//go:linkname exitsyscall
func exitsyscall() {
	gp := getg()

	gp.m.locks++ // see comment in entersyscall
	if sys.GetCallerSP() > gp.syscallsp {
		throw("exitsyscall: syscall frame is no longer valid")
	}

	gp.waitsince = 0
	oldp := gp.m.oldp.ptr()
	gp.m.oldp = 0
	if exitsyscallfast(oldp) {
		// When exitsyscallfast returns success, we have a P so can now use
		// write barriers
		if goroutineProfile.active {
			// Make sure that gp has had its stack written out to the goroutine
			// profile, exactly as it was when the goroutine profiler first
			// stopped the world.
			systemstack(func() {
				tryRecordGoroutineProfileWB(gp)
			})
		}
		trace := traceAcquire()
		if trace.ok() {
			lostP := oldp != gp.m.p.ptr() || gp.m.syscalltick != gp.m.p.ptr().syscalltick
			systemstack(func() {
				// Write out syscall exit eagerly.
				//
				// It's important that we write this *after* we know whether we
				// lost our P or not (determined by exitsyscallfast).
				trace.GoSysExit(lostP)
				if lostP {
					// We lost the P at some point, even though we got it back here.
					// Trace that we're starting again, because there was a traceGoSysBlock
					// call somewhere in exitsyscallfast (indicating that this goroutine
					// had blocked) and we're about to start running again.
					trace.GoStart()
				}
			})
		}
		// There's a cpu for us, so we can run.
		gp.m.p.ptr().syscalltick++
		// We need to cas the status and scan before resuming...
		casgstatus(gp, _Gsyscall, _Grunning)
		if trace.ok() {
			traceRelease(trace)
		}

		// Garbage collector isn't running (since we are),
		// so okay to clear syscallsp.
		gp.syscallsp = 0
		gp.m.locks--
		if gp.preempt {
			// restore the preemption request in case we've cleared it in newstack
			gp.stackguard0 = stackPreempt
		} else {
			// otherwise restore the real stackGuard, we've spoiled it in entersyscall/entersyscallblock
			gp.stackguard0 = gp.stack.lo + stackGuard
		}
		gp.throwsplit = false

		if sched.disable.user && !schedEnabled(gp) {
			// Scheduling of this goroutine is disabled.
			Gosched()
		}

		return
	}

	gp.m.locks--

	// Call the scheduler.
	mcall(exitsyscall0)

	// Scheduler returned, so we're allowed to run now.
	// Delete the syscallsp information that we left for
	// the garbage collector during the system call.
	// Must wait until now because until gosched returns
	// we don't know for sure that the garbage collector
	// is not running.
	gp.syscallsp = 0
	gp.m.p.ptr().syscalltick++
	gp.throwsplit = false
}

// Gosched yields the processor, allowing other goroutines to run. It does not
// suspend the current goroutine, so execution resumes automatically.
//
//go:nosplit
func Gosched() {
	checkTimeouts()
	mcall(gosched_m)
}

// Gosched continuation on g0.
func gosched_m(gp *g) {
	goschedImpl(gp, false)
}

func goschedImpl(gp *g, preempted bool) {
	trace := traceAcquire()
	status := readgstatus(gp)
	if status&^_Gscan != _Grunning {
		dumpgstatus(gp)
		throw("bad g status")
	}
	if trace.ok() {
		// Trace the event before the transition. It may take a
		// stack trace, but we won't own the stack after the
		// transition anymore.
		if preempted {
			trace.GoPreempt()
		} else {
			trace.GoSched()
		}
	}
	casgstatus(gp, _Grunning, _Grunnable)
	if trace.ok() {
		traceRelease(trace)
	}

	dropg()
	lock(&sched.lock)
	globrunqput(gp)
	unlock(&sched.lock)

	if mainStarted {
		wakep()
	}

	schedule()
}

```

## 总结

![](image/Pasted%20image%2020250311083833.png)

## 还存在的问题

![](image/Pasted%20image%2020250311083922.png)

# 抢占式调度

假如有协程不主动挂起，不进行系统调用，执行纯计算任务，还是会存在并发问题，就是[还存在的问题](#问题)里提到的，思路就是不管任何协程都需要调用其他方法，都会对栈进行操作

## 思路

![](image/Pasted%20image%2020250311084508.png)

这个是通过 `go build -gcflags -S main.go` 在汇编中寻找，发现每次调用函数之前都会调用这个方法 runtime.morestack 方法

## morestack

![](image/Pasted%20image%2020250311085217.png)

## 标记抢占

![](image/Pasted%20image%2020250311085317.png)

## 抢占

![](image/Pasted%20image%2020250311100739.png)

 runtime 包下 stubs.go 下的 morestack 方法，具体实现在汇编

```go
func morestack()

// Called during function prolog when more stack is needed.
//
// The traceback routines see morestack on a g0 as being
// the top of a stack (for example, morestack calling newstack
// calling the scheduler calling newm calling gc), so we must
// record an argument size. For that purpose, it has no arguments.
TEXT runtime·morestack(SB),NOSPLIT|NOFRAME,$0-0
	// Cannot grow scheduler stack (m->g0).
	get_tls(CX)
	MOVQ	g(CX), DI     // DI = g
	MOVQ	g_m(DI), BX   // BX = m

	// Set g->sched to context in f.
	MOVQ	0(SP), AX // f's PC
	MOVQ	AX, (g_sched+gobuf_pc)(DI)
	LEAQ	8(SP), AX // f's SP
	MOVQ	AX, (g_sched+gobuf_sp)(DI)
	MOVQ	BP, (g_sched+gobuf_bp)(DI)
	MOVQ	DX, (g_sched+gobuf_ctxt)(DI)

	MOVQ	m_g0(BX), SI  // SI = m.g0
	CMPQ	DI, SI
	JNE	3(PC)
	CALL	runtime·badmorestackg0(SB)
	CALL	runtime·abort(SB)

	// Cannot grow signal stack (m->gsignal).
	MOVQ	m_gsignal(BX), SI
	CMPQ	DI, SI
	JNE	3(PC)
	CALL	runtime·badmorestackgsignal(SB)
	CALL	runtime·abort(SB)

	// Called from f.
	// Set m->morebuf to f's caller.
	NOP	SP	// tell vet SP changed - stop checking offsets
	MOVQ	8(SP), AX	// f's caller's PC
	MOVQ	AX, (m_morebuf+gobuf_pc)(BX)
	LEAQ	16(SP), AX	// f's caller's SP
	MOVQ	AX, (m_morebuf+gobuf_sp)(BX)
	MOVQ	DI, (m_morebuf+gobuf_g)(BX)

	// Call newstack on m->g0's stack.
	MOVQ	m_g0(BX), BX
	MOVQ	BX, g(CX)
	MOVQ	(g_sched+gobuf_sp)(BX), SP
	MOVQ	(g_sched+gobuf_bp)(BX), BP
	CALL	runtime·newstack(SB)
	CALL	runtime·abort(SB)	// crash if newstack returns
	RET
```

### newstack

`preempt := stackguard0 == stackPreempt` 这个就是主要的判断是否抢占的逻辑，后续就回到 schedule 方法，又开始循环

```go

// Goroutine preemption request.  
// 0xfffffade in hex.  
stackPreempt = uintptrMask & -1314

// Called from runtime·morestack when more stack is needed.
// Allocate larger stack and relocate to new stack.
// Stack growth is multiplicative, for constant amortized cost.
//
// g->atomicstatus will be Grunning or Gscanrunning upon entry.
// If the scheduler is trying to stop this g, then it will set preemptStop.
//
// This must be nowritebarrierrec because it can be called as part of
// stack growth from other nowritebarrierrec functions, but the
// compiler doesn't check this.
//
//go:nowritebarrierrec
func newstack() {
	thisg := getg()
	// TODO: double check all gp. shouldn't be getg().
	if thisg.m.morebuf.g.ptr().stackguard0 == stackFork {
		throw("stack growth after fork")
	}
	if thisg.m.morebuf.g.ptr() != thisg.m.curg {
		print("runtime: newstack called from g=", hex(thisg.m.morebuf.g), "\n"+"\tm=", thisg.m, " m->curg=", thisg.m.curg, " m->g0=", thisg.m.g0, " m->gsignal=", thisg.m.gsignal, "\n")
		morebuf := thisg.m.morebuf
		traceback(morebuf.pc, morebuf.sp, morebuf.lr, morebuf.g.ptr())
		throw("runtime: wrong goroutine in newstack")
	}

	gp := thisg.m.curg

	if thisg.m.curg.throwsplit {
		// Update syscallsp, syscallpc in case traceback uses them.
		morebuf := thisg.m.morebuf
		gp.syscallsp = morebuf.sp
		gp.syscallpc = morebuf.pc
		pcname, pcoff := "(unknown)", uintptr(0)
		f := findfunc(gp.sched.pc)
		if f.valid() {
			pcname = funcname(f)
			pcoff = gp.sched.pc - f.entry()
		}
		print("runtime: newstack at ", pcname, "+", hex(pcoff),
			" sp=", hex(gp.sched.sp), " stack=[", hex(gp.stack.lo), ", ", hex(gp.stack.hi), "]\n",
			"\tmorebuf={pc:", hex(morebuf.pc), " sp:", hex(morebuf.sp), " lr:", hex(morebuf.lr), "}\n",
			"\tsched={pc:", hex(gp.sched.pc), " sp:", hex(gp.sched.sp), " lr:", hex(gp.sched.lr), " ctxt:", gp.sched.ctxt, "}\n")

		thisg.m.traceback = 2 // Include runtime frames
		traceback(morebuf.pc, morebuf.sp, morebuf.lr, gp)
		throw("runtime: stack split at bad time")
	}

	morebuf := thisg.m.morebuf
	thisg.m.morebuf.pc = 0
	thisg.m.morebuf.lr = 0
	thisg.m.morebuf.sp = 0
	thisg.m.morebuf.g = 0

	// NOTE: stackguard0 may change underfoot, if another thread
	// is about to try to preempt gp. Read it just once and use that same
	// value now and below.
	stackguard0 := atomic.Loaduintptr(&gp.stackguard0)

	// Be conservative about where we preempt.
	// We are interested in preempting user Go code, not runtime code.
	// If we're holding locks, mallocing, or preemption is disabled, don't
	// preempt.
	// This check is very early in newstack so that even the status change
	// from Grunning to Gwaiting and back doesn't happen in this case.
	// That status change by itself can be viewed as a small preemption,
	// because the GC might change Gwaiting to Gscanwaiting, and then
	// this goroutine has to wait for the GC to finish before continuing.
	// If the GC is in some way dependent on this goroutine (for example,
	// it needs a lock held by the goroutine), that small preemption turns
	// into a real deadlock.
	preempt := stackguard0 == stackPreempt
	if preempt {
		if !canPreemptM(thisg.m) {
			// Let the goroutine keep running for now.
			// gp->preempt is set, so it will be preempted next time.
			gp.stackguard0 = gp.stack.lo + stackGuard
			gogo(&gp.sched) // never return
		}
	}

	if gp.stack.lo == 0 {
		throw("missing stack in newstack")
	}
	sp := gp.sched.sp
	if goarch.ArchFamily == goarch.AMD64 || goarch.ArchFamily == goarch.I386 || goarch.ArchFamily == goarch.WASM {
		// The call to morestack cost a word.
		sp -= goarch.PtrSize
	}
	if stackDebug >= 1 || sp < gp.stack.lo {
		print("runtime: newstack sp=", hex(sp), " stack=[", hex(gp.stack.lo), ", ", hex(gp.stack.hi), "]\n",
			"\tmorebuf={pc:", hex(morebuf.pc), " sp:", hex(morebuf.sp), " lr:", hex(morebuf.lr), "}\n",
			"\tsched={pc:", hex(gp.sched.pc), " sp:", hex(gp.sched.sp), " lr:", hex(gp.sched.lr), " ctxt:", gp.sched.ctxt, "}\n")
	}
	if sp < gp.stack.lo {
		print("runtime: gp=", gp, ", goid=", gp.goid, ", gp->status=", hex(readgstatus(gp)), "\n ")
		print("runtime: split stack overflow: ", hex(sp), " < ", hex(gp.stack.lo), "\n")
		throw("runtime: split stack overflow")
	}

	if preempt {
		if gp == thisg.m.g0 {
			throw("runtime: preempt g0")
		}
		if thisg.m.p == 0 && thisg.m.locks == 0 {
			throw("runtime: g is running but p is not")
		}

		if gp.preemptShrink {
			// We're at a synchronous safe point now, so
			// do the pending stack shrink.
			gp.preemptShrink = false
			shrinkstack(gp)
		}

		if gp.preemptStop {
			preemptPark(gp) // never returns
		}

		// Act like goroutine called runtime.Gosched.
		gopreempt_m(gp) // never return
	}

	// Allocate a bigger segment and move the stack.
	oldsize := gp.stack.hi - gp.stack.lo
	newsize := oldsize * 2

	// Make sure we grow at least as much as needed to fit the new frame.
	// (This is just an optimization - the caller of morestack will
	// recheck the bounds on return.)
	if f := findfunc(gp.sched.pc); f.valid() {
		max := uintptr(funcMaxSPDelta(f))
		needed := max + stackGuard
		used := gp.stack.hi - gp.sched.sp
		for newsize-used < needed {
			newsize *= 2
		}
	}

	if stackguard0 == stackForceMove {
		// Forced stack movement used for debugging.
		// Don't double the stack (or we may quickly run out
		// if this is done repeatedly).
		newsize = oldsize
	}

	if newsize > maxstacksize || newsize > maxstackceiling {
		if maxstacksize < maxstackceiling {
			print("runtime: goroutine stack exceeds ", maxstacksize, "-byte limit\n")
		} else {
			print("runtime: goroutine stack exceeds ", maxstackceiling, "-byte limit\n")
		}
		print("runtime: sp=", hex(sp), " stack=[", hex(gp.stack.lo), ", ", hex(gp.stack.hi), "]\n")
		throw("stack overflow")
	}

	// The goroutine must be executing in order to call newstack,
	// so it must be Grunning (or Gscanrunning).
	casgstatus(gp, _Grunning, _Gcopystack)

	// The concurrent GC will not scan the stack while we are doing the copy since
	// the gp is in a Gcopystack status.
	copystack(gp, newsize)
	if stackDebug >= 1 {
		print("stack grow done\n")
	}
	casgstatus(gp, _Gcopystack, _Grunning)
	gogo(&gp.sched)
}
```

## 基于协作的抢占式调度

编译器在每次调用函数之前插入 morestack 调用，但是存在问题

![](image/Pasted%20image%2020250311113506.png)

多开几个这种协程，线程都会被占住，所以有基于信号的抢占式调度，就是找到某种机制来跳出方法

```go
func do (){
	i := 1
	for true {
		 i++
	}
}
```

## 基于信号的抢占式调度

![](image/Pasted%20image%2020250311114311.png)

![](image/Pasted%20image%2020250311114335.png)

![](image/Pasted%20image%2020250311114424.png)

```go
// doSigPreempt handles a preemption signal on gp.
func doSigPreempt(gp *g, ctxt *sigctxt) {
	// Check if this G wants to be preempted and is safe to
	// preempt.
	if wantAsyncPreempt(gp) {
		if ok, newpc := isAsyncSafePoint(gp, ctxt.sigpc(), ctxt.sigsp(), ctxt.siglr()); ok {
			// Adjust the PC and inject a call to asyncPreempt.
			ctxt.pushCall(abi.FuncPCABI0(asyncPreempt), newpc)
		}
	}

	// Acknowledge the preemption.
	gp.m.preemptGen.Add(1)
	gp.m.signalPending.Store(0)

	if GOOS == "darwin" || GOOS == "ios" {
		pendingPreemptSignals.Add(-1)
	}
}

// asyncPreempt saves all user registers and calls asyncPreempt2.
//
// When stack scanning encounters an asyncPreempt frame, it scans that
// frame and its parent frame conservatively.
//
// asyncPreempt is implemented in assembly.
func asyncPreempt()



// Code generated by mkpreempt.go; DO NOT EDIT.
#include "go_asm.h"
#include "asm_amd64.h"
#include "textflag.h"

TEXT ·asyncPreempt(SB),NOSPLIT|NOFRAME,$0-0
	PUSHQ BP
	MOVQ SP, BP
	// Save flags before clobbering them
	PUSHFQ
	// obj doesn't understand ADD/SUB on SP, but does understand ADJSP
	ADJSP $368
	// But vet doesn't know ADJSP, so suppress vet stack checking
	NOP SP
	MOVQ AX, 0(SP)
	MOVQ CX, 8(SP)
	MOVQ DX, 16(SP)
	MOVQ BX, 24(SP)
	MOVQ SI, 32(SP)
	MOVQ DI, 40(SP)
	MOVQ R8, 48(SP)
	MOVQ R9, 56(SP)
	MOVQ R10, 64(SP)
	MOVQ R11, 72(SP)
	MOVQ R12, 80(SP)
	MOVQ R13, 88(SP)
	MOVQ R14, 96(SP)
	MOVQ R15, 104(SP)
	MOVUPS X0, 112(SP)
	MOVUPS X1, 128(SP)
	MOVUPS X2, 144(SP)
	MOVUPS X3, 160(SP)
	MOVUPS X4, 176(SP)
	MOVUPS X5, 192(SP)
	MOVUPS X6, 208(SP)
	MOVUPS X7, 224(SP)
	MOVUPS X8, 240(SP)
	MOVUPS X9, 256(SP)
	MOVUPS X10, 272(SP)
	MOVUPS X11, 288(SP)
	MOVUPS X12, 304(SP)
	MOVUPS X13, 320(SP)
	MOVUPS X14, 336(SP)
	MOVUPS X15, 352(SP)
	CALL ·asyncPreempt2(SB)
	MOVUPS 352(SP), X15
	MOVUPS 336(SP), X14
	MOVUPS 320(SP), X13
	MOVUPS 304(SP), X12
	MOVUPS 288(SP), X11
	MOVUPS 272(SP), X10
	MOVUPS 256(SP), X9
	MOVUPS 240(SP), X8
	MOVUPS 224(SP), X7
	MOVUPS 208(SP), X6
	MOVUPS 192(SP), X5
	MOVUPS 176(SP), X4
	MOVUPS 160(SP), X3
	MOVUPS 144(SP), X2
	MOVUPS 128(SP), X1
	MOVUPS 112(SP), X0
	MOVQ 104(SP), R15
	MOVQ 96(SP), R14
	MOVQ 88(SP), R13
	MOVQ 80(SP), R12
	MOVQ 72(SP), R11
	MOVQ 64(SP), R10
	MOVQ 56(SP), R9
	MOVQ 48(SP), R8
	MOVQ 40(SP), DI
	MOVQ 32(SP), SI
	MOVQ 24(SP), BX
	MOVQ 16(SP), DX
	MOVQ 8(SP), CX
	MOVQ 0(SP), AX
	ADJSP $-368
	POPFQ
	POPQ BP
	RET

//go:nosplit  
func asyncPreempt2() {  
    gp := getg()  
    gp.asyncSafePoint = true  
    if gp.preemptStop {  
       mcall(preemptPark)  
    } else {  
       mcall(gopreempt_m)  
    }  
    gp.asyncSafePoint = false  
}

// preemptPark parks gp and puts it in _Gpreempted.
//
//go:systemstack
func preemptPark(gp *g) {
	status := readgstatus(gp)
	if status&^_Gscan != _Grunning {
		dumpgstatus(gp)
		throw("bad g status")
	}

	if gp.asyncSafePoint {
		// Double-check that async preemption does not
		// happen in SPWRITE assembly functions.
		// isAsyncSafePoint must exclude this case.
		f := findfunc(gp.sched.pc)
		if !f.valid() {
			throw("preempt at unknown pc")
		}
		if f.flag&abi.FuncFlagSPWrite != 0 {
			println("runtime: unexpected SPWRITE function", funcname(f), "in async preempt")
			throw("preempt SPWRITE")
		}
	}

	// Transition from _Grunning to _Gscan|_Gpreempted. We can't
	// be in _Grunning when we dropg because then we'd be running
	// without an M, but the moment we're in _Gpreempted,
	// something could claim this G before we've fully cleaned it
	// up. Hence, we set the scan bit to lock down further
	// transitions until we can dropg.
	casGToPreemptScan(gp, _Grunning, _Gscan|_Gpreempted)
	dropg()

	// Be careful about how we trace this next event. The ordering
	// is subtle.
	//
	// The moment we CAS into _Gpreempted, suspendG could CAS to
	// _Gwaiting, do its work, and ready the goroutine. All of
	// this could happen before we even get the chance to emit
	// an event. The end result is that the events could appear
	// out of order, and the tracer generally assumes the scheduler
	// takes care of the ordering between GoPark and GoUnpark.
	//
	// The answer here is simple: emit the event while we still hold
	// the _Gscan bit on the goroutine. We still need to traceAcquire
	// and traceRelease across the CAS because the tracer could be
	// what's calling suspendG in the first place, and we want the
	// CAS and event emission to appear atomic to the tracer.
	trace := traceAcquire()
	if trace.ok() {
		trace.GoPark(traceBlockPreempted, 0)
	}
	casfrom_Gscanstatus(gp, _Gscan|_Gpreempted, _Gpreempted)
	if trace.ok() {
		traceRelease(trace)
	}
	schedule()
}
```

## 总结

![](image/Pasted%20image%2020250311120012.png)

# 协程太多有什么问题

## 无限开启协程

```go
package main  
  
import (  
    "fmt"  
    "math"    "time")  
  
func main() {  
    for i := 0; i < math.MaxInt32; i++ {  
       go func(i int) {  
          fmt.Println(i)  
          time.Sleep(time.Second)  
       }(i)  
    }  
    time.Sleep(time.Hour)  
}
```

产生了报错 `panic: too many concurrent operations on a single file or socket (max 1048575)`

## 协程太多带来的问题

![](image/Pasted%20image%2020250311131232.png)

## 处理协程太多方案

![](image/Pasted%20image%2020250311131350.png)

### 优化业务逻辑

这是最根本的

### 利用 channel 的缓存区

![](image/Pasted%20image%2020250311134036.png)

```go
package main  
  
import (  
    "fmt"  
    "math"    "time")  
  
func main() {  
    c := make(chan struct{}, 3000)  
    for i := 0; i < math.MaxInt32; i++ {  
       c <- struct{}{}  
       go func(i int, c chan struct{}) {  
          fmt.Println(i)  
          time.Sleep(time.Second)  
          <-c  
       }(i, c)  
    }  
    time.Sleep(time.Hour)  
}
```

### 协程池

![](image/Pasted%20image%2020250311134233.png)

![](image/Pasted%20image%2020250311134258.png)

### 调整系统资源

## 总结

![](image/Pasted%20image%2020250311134344.png)

# 小结

## 为什么用协程

![](image/Pasted%20image%2020250311134441.png)

## 协程是什么

![](image/Pasted%20image%2020250311134548.png)

## GMP 模型

![](image/Pasted%20image%2020250311134614.png)

![](image/Pasted%20image%2020250311134623.png)

## 协程并发

![](image/Pasted%20image%2020250311134643.png)

![](image/Pasted%20image%2020250311134659.png)

## 抢占式调度

![](image/Pasted%20image%2020250311134754.png)

