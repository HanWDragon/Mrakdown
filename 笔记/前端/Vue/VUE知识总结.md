# 序

## 需要学习 Vue 3 吗？

在2020年的9月19日，万众期待的Vue3终于发布了正式版，命名为“One Piece”

- 它也带来了很多新的特性：更好的性能、更小的包体积、更好的TypeScript集成、更优秀的API设计
- 在vue3刚刚发布时，很多人也是跃跃欲试，想要尝试vue3的各种新特性
- 但是事实上在刚刚发布的时候我们使用vue3来写demo练习是没有问题的，真正在实际业务项目中使用vue3还需要一个相对的过程
- 包括vue3的进一步稳定、包括社区更多vue3相关的插件、组件库的支持和完善。

那么现在是否是学习vue3的时间

- 答案是肯定的
- 首先vue3在经过一系列的更新和维护后，已经是趋于稳定，并且在之前尤雨溪也宣布在今年（2021年）第二季度会将vue3作为Vue CLI的默认版本了
- 目前社区也经过一定时间的沉淀，更加的完善了，包括AntDesignVue、Element-Plus都提供了对Vue3的支持，所以很多公司目前新的项目都已经在使用Vue3来进行开发了
- 并且在面试的时候，几乎都会问到各种各样Vue3、Vite2工具相关的问题
## Vue 3 带来的变化

### 源码

源码通过monorepo的形式来管理源代码：

- Mono：单个
- Repo：repository仓库
- 主要是将许多项目的代码存储在同一个repository中
- 这样做的目的是多个包本身相互独立，可以有自己的功能逻辑、单元测试等，同时又在同一个仓库下方便管理
- 而且模块划分的更加清晰，可维护性、可扩展性更强；

源码使用TypeScript来进行重写

- 在Vue2.x的时候，Vue使用Flow来进行类型检测
- 在Vue3.x的时候，Vue的源码全部使用TypeScript来进行重构，并且Vue本身对TypeScript支持也更好了

### 性能

使用Proxy进行数据劫持

- 在Vue2.x的时候，Vue2是使用Object.defineProperty来劫持数据的getter和setter方法的
- 这种方式一致存在一个缺陷就是当给对象添加或者删除属性时，是无法劫持和监听的
- 所以在Vue2.x的时候，不得不提供一些特殊的API，比如`$set`或`$delete`，事实上都是一些hack方法，也增加了开发者学习新的API的成本
- 而在Vue3.x开始，Vue使用Proxy来实现数据的劫持

删除了一些不必要的API

- 移除了实例上的$on, $off 和 $once
- 移除了一些特性：如filter、内联模板等
- 包括编译方面的优化
- 生成Block Tree、Slot编译优化、diff算法优化

### 新的API

由 Options API 到 Composition API

- 在Vue2.x的时候，我们会通过Options API来描述组件对象
- Options API包括data、props、methods、computed、生命周期等等这些选项
- 存在比较大的问题是多个逻辑可能是在不同的地方
	- 比如created中会使用某一个method来修改data的数据，代码的内聚性非常差、
- Composition API可以将相关联的代码放到同一处 进行处理，而不需要在多个Options之间寻找；

Hooks函数增加代码的复用性

- 在Vue2.x的时候，我们通常通过 mixins 在多个组件之间共享逻辑
- 但是有一个很大的缺陷就是 mixins 也是由一大堆的Options组成的，并且多个 mixins 会存在命名冲突的问题
- 在 Vue3.x 中，我们可以通过 Hook 函数，来将一部分独立的逻辑抽取出去，并且它们还可以做到是响应式的

## 案例对比

如果我们希望实现一个计数器的案例

- 点击+1，那么内容会显示数字+1
- 点击-1，那么内容会显示数字-1

我们可以选择很多种方式来实现

- 在这里我们就对比原生和Vue的实现方式的不同

### 原生


```html
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
  </head>
  <body>
    <h2 class="counter">0</h2>
    <button class="increment">+1</button>
    <button class="decrement">-1</button>

    <script>
      // 1.获取所有的元素
      const counterEl = document.querySelector(".counter");
      const incrementEl = document.querySelector(".increment");
      const decrementEl = document.querySelector(".decrement");

      // 2.定义变量
      let counter = 100;
      counterEl.innerHTML = counter;

      // 3.监听按钮的点击
      incrementEl.addEventListener("click", () => {
        counter += 1;
        counterEl.innerHTML = counter;
      });
      decrementEl.addEventListener("click", () => {
        counter -= 1;
        counterEl.innerHTML = counter;
      });
    </script>
  </body>
</html>

```


### Vue


```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app">哈哈哈哈啊</div>

  <script src="../js/vue.js"></script>
  <script>
    Vue.createApp({
      template: `
        <div>
          <h2>{{message}}</h2>
          <h2>{{counter}}</h2>
          <button @click='increment'>+1</button>
          <button @click='decrement'>-1</button>
        </div>
      `,
      data: function() {
        return {
          message: "Hello World",
          counter: 100
        }
      },
      // 定义各种各样的方法
      methods: {
        increment() {
          console.log("点击了+1");
          this.counter++;
        },
        decrement() {
          console.log("点击了-1");
          this.counter--;
        }
      }
    }).mount('#app');
  </script>
</body>
</html>
```

## 声明式和命令式

原生开发和Vue开发的模式和特点，我们会发现是完全不同的，这里其实涉及到两种不同的编程范式

- 命令式编程和声明式编程
- 命令式编程关注的是 “how to do”，声明式编程关注的是 “what to do”，由框架(机器)完成 “how”的过程

在原生的实现过程中，我们是如何操作的呢？

- 我们每完成一个操作，都需要通过JavaScript编写一条代码，来给浏览器一个指令
- 这样的编写代码的过程，我们称之为命令式编程
- 在早期的原生JavaScript和jQuery开发的过程中，我们都是通过这种命令式的方式在编写代码的；

在Vue的实现过程中，我们是如何操作的呢

- 我们会在createApp传入的对象中声明需要的内容，模板template、数据data、方法methods
- 这样的编写代码的过程，我们称之为是声明式编程
- 目前Vue、React、Angular的编程模式，我们称之为声明式编程

## MVVM 模型

MVC和MVVM都是一种软件的体系结构

- MVC是Model – View –Controller的简称，是在前期被使用非常框架的架构模式，比如iOS、前端
- MVVM是Model-View-ViewModel的简称，是目前非常流行的架构模式
- 通常情况下，我们也经常称Vue是一个MVVM的框架
- Vue官方其实有说明，Vue虽然并没有完全遵守MVVM的模型，但是整个设计是受到它的启发的

![](image/Pasted%20image%2020250708212318.png)

## Vue 的源码

如果想要学习Vue的源码，比如看createApp的实现过程，应该怎么办呢

1. 在GitHub上搜索 vue-next，下载源代码
	- 这里推荐通过 git clone 的方式下载
2. 第二步：安装Vue源码项目相关的依赖
	- 执行 yarn install
3. 第三步：对项目执行打包操作
	- 执行yarn dev（执行前修改脚本）
![](image/Pasted%20image%2020250708214753.png)
4. 通过 packages/vue/dist/vue.global.js 调试代码

# 模板语法

## template属性

在使用createApp的时候，我们传入了一个对象，接下来我们详细解析一下之前传入的属性分别代表什么含义

- template属性：表示的是Vue需要帮助我们渲染的模板信息
	- 目前我们看到它里面有很多的HTML标签，这些标签会替换掉我们挂载到的元素（比如id为app的div）的innerHTML
	- 模板中有一些奇怪的语法，比如 {{}}，比如 @click，这些都是模板特有的语法
- 但是这个模板的写法有点过于别扭了，并且IDE很有可能没有任何提示，阻碍我们编程的效率。

Vue提供了两种方式

1. 使用script标签，并且标记它的类型为 x-template
2. 使用任意标签（通常使用template标签，因为不会被浏览器渲染），设置id
	- template元素是一种用于保存客户端内容的机制，该内容再加载页面时不会被呈现，但随后可以在运行时使用JavaScript实例化

### template写法

#### 使用 script 标签

这个时候，在createApp的对象中，我们需要传入的template以 # 开头

- 如果字符串是以 # 开始，那么它将被用作 querySelector，并且使用匹配元素的 innerHTML 作为模板字符串

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app">哈哈哈哈啊</div>

  <script type="x-template" id="why">
    <div>
      <h2>{{message}}</h2>
      <h2>{{counter}}</h2>
      <button @click='increment'>+1</button>
      <button @click='decrement'>-1</button>
    </div>
  </script>

  <script src="../js/vue.js"></script>
  <script>
    document.querySelector("#why")
    Vue.createApp({
      template: '#why',
      data: function() {
        return {
          message: "Hello World",
          counter: 100
        }
      },
      // 定义各种各样的方法
      methods: {
        increment() {
          console.log("点击了+1");
          this.counter++;
        },
        decrement() {
          console.log("点击了-1");
          this.counter--;
        }
      }
    }).mount('#app');
  </script>
</body>
</html>
```

#### 使用 template

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="why">
    <div>
      <h2>{{message}}</h2>
      <h2>{{counter}}</h2>
      <button @click='increment'>+1</button>
      <button @click='decrement'>-1</button>
      <button @click="btnClick">按钮</button>
    </div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    document.querySelector("#why")
    Vue.createApp({
      template: '#why',
      data: function() {
        return {
          message: "Hello World",
          counter: 100
        }
      },
      // 定义各种各样的方法
      methods: {
        increment() {
          console.log("点击了+1");
          this.counter++;
        },
        decrement() {
          console.log("点击了-1");
          this.counter--;
        },
        btnClick: () => {
          // this === window? 不可以
          // 写成一个箭头函数时, 这个this就是window
          // 在箭头函数中是不绑定this, 但是函数中如果使用了this
          console.log(this);
        },
        btn2Click: function() {
          // this === window? 不可以
          // 写成一个箭头函数时, 这个this就是window
          // 在箭头函数中是不绑定this, 但是函数中如果使用了this
          console.log(this);
        }
      }
    }).mount('#app');

  </script>
</body>
</html>
```

## data 属性

data 属性是传入一个函数，并且该函数需要返回一个对象

- 在Vue2.x的时候，也可以传入一个对象（虽然官方推荐是一个函数）
- 在Vue3.x的时候，必须传入一个函数，否则就会直接在浏览器中报错

data中返回的对象会被Vue的响应式系统劫持，之后对该对象的修改或者访问都会在劫持中被处理

- 所以我们在template中通过 {{counter}} 访问counter，可以从对象中获取到数据
- 所以我们修改counter的值时，template中的 {{counter}}也会发生改变

## methods 属性

methods属性是一个对象，通常我们会在这个对象中定义很多的方法：

- 这些方法可以被绑定到 template 模板中
- 在该方法中，我们可以使用this关键字来直接访问到data中返回的对象的属性；

对于有经验的同学，在这里我提一个问题，官方文档有这么一段描述：

1. 为什么不能使用箭头函数（官方文档有给出解释）
2. 不使用箭头函数的情况下，this到底指向的是什么？（可以作为一道面试题）

![](image/Pasted%20image%2020250708214514.png)

### 不能使用箭头函数

我们在methods中要使用data返回对象中的数据

- 那么这个this是必须有值的，并且应该可以通过this获取到data返回对象中的数据。

那么我们这个this能不能是window呢

- 不可以是window，因为window中我们无法获取到data返回对象中的数据
- 但是如果我们使用箭头函数，那么这个this就会是window了

为什么是window呢

- 这里涉及到箭头函数使用this的查找规则，它会在自己的上层作用域中来查找this
- 最终刚好找到的是script作用域中的this，所以就是window

### this到底指向什么

-  事实上Vue的源码当中就是对methods中的所有函数进行了遍历，并且通过bind绑定了this

![](image/Pasted%20image%2020250708221227.png)

## Mustache双大括号语法

如果我们希望把数据显示到模板（template）中，使用最多的语法是 “Mustache”语法 (双大括号) 的文本插值

- 并且我们前端提到过，data返回的对象是有添加到Vue的响应式系统中
- 当data中的数据发生改变时，对应的内容也会发生更新
- 当然，Mustache中不仅仅可以是data中的属性，也可以是一个JavaScript的表达式

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <!-- 1.mustache的基本使用 -->
    <h2>{{message}} - {{message}}</h2>
    <!-- 2.是一个表达式 -->
    <h2>{{counter * 10}}</h2>
    <h2>{{ message.split(" ").reverse().join(" ") }}</h2>
    <!-- 3.也可以调用函数 -->
    <!-- 可以使用computed(计算属性) -->
    <h2>{{getReverseMessage()}}</h2>
    <!-- 4.三元运算符 -->
    <h2>{{ isShow ? "哈哈哈": "" }}</h2>
    <button @click="toggle">切换</button>

    <!-- 错误用法 -->
    <!-- var name = "abc" -> 赋值语句 -->
    <!-- <h2>{{var name = "abc"}}</h2>
    <h2>{{ if(isShow) {  return "哈哈哈" } }}</h2> -->
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          counter: 100,
          isShow: true
        }
      },
      methods: {
        getReverseMessage() {
          return this.message.split(" ").reverse().join(" ");
        },
        toggle() {
          this.isShow = !this.isShow;
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-once指令

v-once用于指定元素或者组件只渲染一次

- 当数据发生变化时，元素或者组件以及其所有的子元素将视为静态内容并且跳过
- 如果是子节点，也是只会渲染一次
- 该指令可以用于性能优化

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>{{counter}}</h2>
    <div v-once>
      <h2>{{counter}}</h2>
      <h2>{{message}}</h2>
    </div>
    <button @click="increment">+1</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          counter: 100,
          message: "abc"
        }
      },
      methods: {
        increment() {
          this.counter++;
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-text指令

用于更新元素的 textContent

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-text="message"></h2>
    <h2>{{message}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-html

默认情况下，如果我们展示的内容本身是 html 的，那么vue并不会对其进行特殊的解析

- 如果我们希望这个内容被Vue可以解析出来，那么可以使用 v-html 来展示

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div>{{msg}}</div>
    <div v-html="msg"></div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          msg: '<span style="color:red; background: blue;">哈哈哈</span>'
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-pre

v-pre用于跳过元素和它的子元素的编译过程，显示原始的Mustache标签

- 跳过不需要编译的节点，加快编译的速度

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-pre>{{message}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-cloak

这个指令保持在元素上直到关联组件实例结束编译

- 和 CSS 规则如 `[v-cloak] { display: none }` 一起用时，这个指令可以隐藏未编译的 Mustache 标签直到组件实例准备完毕
- `<div>` 不会显示，直到编译结束

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    [v-cloak] {
      display: none;
    }
  </style>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-cloak>{{message}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-bind

上面讲的一系列指令，主要是将值插入到模板内容中。

但是，除了内容需要动态来决定外，某些属性我们也希望动态来绑定

- 比如动态绑定a元素的href属性
- 比如动态绑定img元素的src属性

绑定属性我们使用v-bind

- 缩写：:
- 预期：any (with argument) | Object (without argument)
- 参数：attrOrProp (optional)
- 修饰符：
	- camel - 将 kebab-case attribute 名转换为 camelCase
- 用法：动态地绑定一个或多个 attribute，或一个组件 prop 到表达式

### 绑定基本属性

v-bind用于绑定一个或多个属性值，或者向另一个组件传递props值

- 在开发中，有哪些属性需要动态进行绑定呢
	- 还是有很多的，比如图片的链接src、网站的链接href、动态绑定一些类、样式等等

 v-bind有一个对应的语法糖，也就是简写方式
 
 - 在开发中，我们通常会使用语法糖的形式，因为这样更加简洁

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <!-- vue2 template模板中只能有一个根元素 -->
  <!-- vue3 是允许template中有多个根元素 -->
  <template id="my-app">
    <!-- 1.v-bind的基本使用 -->
    <img v-bind:src="imgUrl" alt="">
    <a v-bind:href="link">百度一下</a>

    <!-- 2.v-bind提供一个语法糖 : -->
    <img :src="imgUrl" alt="">
    <img src="imgUrl" alt="">
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          imgUrl: "https://avatars.githubusercontent.com/u/10335230?s=60&v=4",
          link: "https://www.baidu.com"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 绑定class

在开发中，有时候我们的元素class也是动态的

- 当数据为某个状态时，字体显示红色
- 当数据另一个状态时，字体显示黑色。

绑定class有两种方式

- 对象语法
- 数组语法

#### 对象语法

对象语法：我们可以传给 :class (v-bind:class 的简写) 一个对象，以动态地切换 class

```vue
<!DOCTYPE html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta http-equiv="X-UA-Compatible" content="IE=edge" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Document</title>
    <style>
      .active {
        color: red;
      }
    </style>
  </head>
  <body>
    <div id="app"></div>

    <template id="my-app">
      <div :class="className">哈哈哈哈</div>
      <!-- 对象语法: {'active': boolean} -->
      <div :class="{'active': isActive}">呵呵呵呵</div>
      <button @click="toggle">切换</button>

      <!-- 也可以有多个键值对 -->
      <div :class="{active: isActive, title: true}">呵呵呵呵</div>

      <!-- 默认的class和动态的class结合 -->
      <div class="abc cba" :class="{active: isActive, title: true}">
        呵呵呵呵
      </div>

      <!-- 将对象放到一个单独的属性中 -->
      <div class="abc cba" :class="classObj">呵呵呵呵</div>

      <!-- 将返回的对象放到一个methods(computed)方法中 -->
      <div class="abc cba" :class="getClassObj()">呵呵呵呵</div>      
    </template>

    <script src="../js/vue.js"></script>
    <script>
      const App = {
        template: "#my-app",
        data() {
          return {
            className: "why",
            isActive: true,
            title: "abc",
            classObj: { 
              active: true, 
              title: true 
            },
          };
        },
        methods: {
          toggle() {
            this.isActive = !this.isActive;
          },
          getClassObj() {
            return { 
              active: true, 
              title: true 
            }
          }
        },
      };

      Vue.createApp(App).mount("#app");
    </script>
  </body>
</html>

```

#### 数组语法

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div :class="['abc', title]">哈哈哈哈</div>
    <div :class="['abc', title, isActive ? 'active': '']">哈哈哈哈</div>
    <div :class="['abc', title, {active: isActive}]">哈哈哈哈</div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          title: "cba",
          isActive: true
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 绑定style

#### 对象语法

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <!-- :style="{cssPropertyName: cssPropertyValue}" -->
    <div :style="{color: finalColor, 'font-size': '30px'}">哈哈哈哈</div>
    <div :style="{color: finalColor, fontSize: '30px'}">哈哈哈哈</div>
    <div :style="{color: finalColor, fontSize: finalFontSize + 'px'}">哈哈哈哈</div>

    <!-- 绑定一个data中的属性值, 并且是一个对象 -->
    <div :style="finalStyleObj">呵呵呵呵</div>
    <!-- 调用一个方法 -->
    <div :style="getFinalStyleObj()">呵呵呵呵</div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          finalColor: 'red',
          finalFontSize: 50,
          finalStyleObj: {
            'font-size': '50px',
            fontWeight: 700,
            backgroundColor: 'red'
          }
        }
      },
      methods: {
        getFinalStyleObj() {
          return {
            'font-size': '50px',
            fontWeight: 700,
            backgroundColor: 'red'
          }
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

#### 数组语法

:style 的数组语法可以将多个样式对象应用到同一个元素上

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div :style="[style1Obj, style2Obj]">哈哈哈</div>
    <img :src="" alt="">
    <a :href=""></a>
    <div :class></div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          style1Obj: {
            color: 'red',
            fontSize: '30px'
          },
          style2Obj: {
            textDecoration: "underline"
          }
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 动态绑定属性

在某些情况下，我们属性的名称可能也不是固定的

- 前端我们无论绑定src、href、class、style，属性名称都是固定的
- 如果属性名称不是固定的，我们可以使用 `:[属性名]=“值”` 的格式来定义
- 这种绑定的方式，我们称之为动态绑定属性

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div :[name]="value">哈哈哈</div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          name: "cba",
          value: "kobe"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 绑定一个对象

如果我们希望将一个对象的所有属性，绑定到元素上的所有属性

- 非常简单，我们可以直接使用 v-bind 绑定一个 对象

案例：info对象会被拆解成div的各个属性

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div v-bind="info">哈哈哈哈</div>
    <div :="info">哈哈哈哈</div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          info: {
            name: "why",
            age: 18,
            height: 1.88
          }
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## v-on

前面我们绑定了元素的内容和属性，在前端开发中另外一个非常重要的特性就是交互。

在前端开发中，我们需要经常和用户进行各种各样的交互

- 这个时候，我们就必须监听用户发生的事件，比如点击、拖拽、键盘事件等等
- 在Vue中如何监听事件呢？使用v-on指令

### 介绍

v-on的使用

- 缩写：@
- 预期：Function | Inline Statement | Object
- 参数：event
- 修饰符
	- .stop - 调用 event.stopPropagation()
	- .prevent - 调用 event.preventDefault()
	- .capture - 添加事件侦听器时使用 capture 模式
	- .self - 只当事件是从侦听器绑定的元素本身触发时才触发回调
	- .{keyAlias} - 仅当事件是从特定键触发时才触发回调
	- .once - 只触发一次回调
	- .left - 只当点击鼠标左键时触发
	- .right - 只当点击鼠标右键时触发
	- .middle - 只当点击鼠标中键时触发
	- .passive - { passive: true } 模式添加侦听器

用法：绑定事件监听

### 用法

我们可以使用v-on来监听一下点击的事件

v-on:click可以写成@click，是它的语法糖写法

当然，我们也可以绑定其他的事件

如果我们希望一个元素绑定多个事件，这个时候可以传入一个对象

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>

  <style>
    .area {
      width: 200px;
      height: 200px;
      background: red;
    }
  </style>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <!-- 完整写法: v-on:监听的事件="methods中方法" -->
    <button v-on:click="btn1Click">按钮1</button>
    <div class="area" v-on:mousemove="mouseMove">div</div>
    <!-- 语法糖 -->
    <button @click="btn1Click">按钮1</button>
    <!-- 绑定一个表达式: inline statement -->
    <button @click="counter++">{{counter}}</button>
    <!-- 绑定一个对象 -->
    <div class="area" v-on="{click: btn1Click, mousemove: mouseMove}"></div>
    <div class="area" @="{click: btn1Click, mousemove: mouseMove}"></div>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          counter: 100
        }
      },
      methods: {
        btn1Click() {
          console.log("按钮1发生了点击");
        },
        mouseMove() {
          console.log("鼠标移动");
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>   
```

### 参数传递

当通过methods中定义方法，以供@click调用时，需要注意参数问题：

1. 如果该方法不需要额外参数，那么方法后的()可以不添加，但是注意：如果方法本身中有一个参数，那么会默认将原生事件event参数传递进去
2. 如果需要同时传入某个参数，同时需要event时，可以通过$event传入事件

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <!-- 默认传入event对象, 可以在方法中获取 -->
    <button @click="btn1Click">按钮1</button>
    <!-- $event可以获取到事件发生时的事件对象 -->
    <button @click="btn2Click($event, 'coderwhy', 18)">按钮2</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World"
        }
      },
      methods: {
        btn1Click(event) {
          console.log(event);
        },
        btn2Click(event, name, age) {
          console.log(name, age, event);
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 修饰符

v-on支持修饰符，修饰符相当于对事件进行了一些特殊的处理：

- .stop - 调用 event.stopPropagation()
- .prevent - 调用 event.preventDefault()
- .capture - 添加事件侦听器时使用 capture 模式
- .self - 只当事件是从侦听器绑定的元素本身触发时才触发回调
- .{keyAlias} - 仅当事件是从特定键触发时才触发回调
- .once - 只触发一次回调
- .left - 只当点击鼠标左键时触发
- .right - 只当点击鼠标右键时触发
- .middle - 只当点击鼠标中键时触发
- .passive - { passive: true } 模式添加侦听器

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <div @click="divClick">
      <button @click.stop="btnClick">按钮</button>
    </div>
    <input type="text" @keyup.enter="enterKeyup">
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World"
        }
      },
      methods: {
        divClick() {
          console.log("divClick");
        },
        btnClick() {
          console.log('btnClick');
        },
        enterKeyup(event) {
          console.log("keyup", event.target.value);
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## 条件渲染

在某些情况下，我们需要根据当前的条件决定某些元素或组件是否渲染，这个时候我们就需要进行条件判断了

Vue提供了下面的指令来进行条件判断

- v-if
- v-else
- v-else-if
- v-show

### v-if、v-else、v-else-if

v-if、v-else、v-else-if用于根据条件来渲染某一块的内容

- 这些内容只有在条件为true时，才会被渲染出来
- 这三个指令与JavaScript的条件语句if、else、else if类似

v-if的渲染原理

- v-if是惰性的
- 当条件为false时，其判断的内容完全不会被渲染或者会被销毁掉
- 当条件为true时，才会真正渲染条件块中的内容

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-if="isShow">哈哈哈哈</h2>
    <button @click="toggle">切换</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          message: "Hello World",
          isShow: true
        }
      },
      methods: {
        toggle() {
          this.isShow = !this.isShow;
        }
      }
    }

    Vue.createApp(App).mount('#app');

    // JavaScript条件判断
    if (true) {

    }
  </script>
</body>
</html>
```

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <input type="text" v-model="score">
    <h2 v-if="score > 90">优秀</h2>
    <h2 v-else-if="score > 60">良好</h2>
    <h2 v-else>不及格</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          score: 95
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### template元素

因为v-if是一个指令，所以必须将其添加到一个元素上

- 但是如果我们希望切换的是多个元素呢
- 此时我们渲染div，但是我们并不希望div这种元素被渲染
- 这个时候，我们可以选择使用template

template元素可以当做不可见的包裹元素，并且在v-if上使用，但是最终template不会被渲染出来

- 有点类似于小程序中的block

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <template v-if="isShowHa">
      <h2>哈哈哈哈</h2>
      <h2>哈哈哈哈</h2>
      <h2>哈哈哈哈</h2>
    </template>

    <template v-else>
      <h2>呵呵呵呵</h2>
      <h2>呵呵呵呵</h2>
      <h2>呵呵呵呵</h2>
    </template>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          isShowHa: true
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### v-show

v-show和v-if的用法看起来是一致的，也是根据一个条件决定是否显示元素或者组件

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-show="isShow">哈哈哈哈</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          isShow: true
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### v-show和v-if的区别

首先，在用法上的区别

- v-show是不支持template
- v-show不可以和v-else一起使用

其次，本质的区别

- v-show元素无论是否需要显示到浏览器上，它的DOM实际都是有渲染的，只是通过CSS的display属性来进行切换
- v-if当条件为false时，其对应的原生压根不会被渲染到DOM中

开发中如何进行选择呢

- 如果我们的原生需要在显示和隐藏之间频繁的切换，那么使用v-show
- 如果不会频繁的发生切换，那么使用v-if

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2 v-if="isShow">哈哈哈哈</h2>
    <h2 v-show="isShow">呵呵呵呵</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          isShow: true
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## 列表渲染

在真实开发中，我们往往会从服务器拿到一组数据，并且需要对其进行渲染

- 这个时候我们可以使用v-for来完成
- v-for类似于JavaScript的for循环，可以用于遍历一组数据

### v-for基本使用

v-for的基本格式是 "item in 数组"：

- 数组通常是来自data或者prop，也可以是其他方式
- item是我们给每项元素起的一个别名，别名可以自定义

我们知道，在遍历一个数组的时候会经常需要拿到数组的索引

- 如果我们需要索引，可以使用格式： "(item, index) in 数组"
- 注意上面的顺序：数组元素项item是在前面的，索引项index是在后面的

### v-for支持的类型

v-for也支持遍历对象，并且支持有一二三个参数：

- 一个参数： "value in object"
- 二个参数： "(value, key) in object"
- 三个参数： "(value, key, index) in object"

v-for同时也支持数字的遍历

- 每一个item都是一个数字

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>电影列表</h2>
    <ul>
      <!-- 遍历数组 -->
      <li v-for="(movie, index) in movies">{{index+1}}.{{movie}}</li>
    </ul>
    <h2>个人信息</h2>
    <ul>
      <!-- 遍历对象 -->
      <li v-for="(value, key, index) in info">{{value}}-{{key}}-{{index}}</li>
    </ul>
    <h2>遍历数字</h2>
    <ul>
      <li v-for="(num, index) in 10">{{num}}-{{index}}</li>
    </ul>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          movies: [
            "星际穿越",
            "盗梦空间",
            "大话西游",
            "教父",
            "少年派"
          ],
          info: {
            name: "why",
            age: 18,
            height: 1.88
          }
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### template元素

类似于v-if，你可以使用 template 元素来循环渲染一段包含多个元素的内容

- 我们使用template来对多个元素进行包裹，而不是使用div来完成

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <ul>
      <template v-for="(value, key) in info">
        <li>{{key}}</li>
        <li>{{value}}</li>
        <li class="divider"></li>
      </template>
    </ul>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          info: {
            name: "why",
            age: 18,
            height: 1.88
          }
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 数组更新检测

Vue 将被侦听的数组的变更方法进行了包裹，所以它们也将会触发视图更新。这些被包裹过的方法包括

- push()
- pop()
- shift()
- unshift()
- splice()
- sort()
- reverse()

替换数组的方法

- 上面的方法会直接修改原来的数组，但是某些方法不会替换原来的数组，而是会生成新的数组，比如 filter()、concat() 和 slice()

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>电影列表</h2>
    <ul>
      <li v-for="(movie, index) in movies">{{index+1}}.{{movie}}</li>
    </ul>
    <input type="text" v-model="newMovie">
    <button @click="addMovie">添加电影</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          newMovie: "",
          movies: [
            "星际穿越",
            "盗梦空间",
            "大话西游",
            "教父",
            "少年派"
          ]
        }
      },
      methods: {
        addMovie() {
          this.movies.push(this.newMovie);
          this.newMovie = "";

          // this.movies = this.movies.filter(item => item.length > 2);
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### v-for中的key的作用

在使用v-for进行列表渲染时，我们通常会给元素或者组件绑定一个key属性

这个key属性有什么作用呢？我们先来看一下官方的解释：

- key属性主要用在Vue的虚拟DOM算法，在新旧nodes对比时辨识VNodes
- 如果不使用key，Vue会使用一种最大限度减少动态元素并且尽可能的尝试就地修改/复用相同类型元素的算法
- 而使用key时，它会基于key的变化重新排列元素顺序，并且会移除/销毁key不存在的元素；

官方的解释对于初学者来说并不好理解，比如下面的问题：

- 什么是新旧nodes，什么是VNode
- 没有key的时候，如何尝试修改和复用的
- 有key的时候，如何基于key重新排列的

说白了就是Vue和React这些框架更新的范围都是组件级别，不能精确到元素，所以需要使用虚拟Dom来优化找到修改的元素

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <ul>
      <li v-for="item in letters" :key="item">{{item}}</li>
    </ul>
    <button @click="insertF">插入F元素</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          letters: ['a', 'b', 'c', 'd']
        }
      },
      methods: {
        insertF() {
          this.letters.splice(2, 0, 'f')
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

#### 认识VNode

 我们先来解释一下VNode的概念：

- VNode的全称是Virtual Node，也就是虚拟节点
- 事实上，无论是组件还是元素，它们最终在Vue中表示出来的都是一个个VNode
- VNode的本质是一个JavaScript的对象

![](image/Pasted%20image%2020250709115511.png)

#### 虚拟DOM

如果我们不只是一个简单的div，而是有一大堆的元素，那么它们应该会形成一个VNode Tree

![](image/Pasted%20image%2020250709115609.png)

#### 插入F的案例

我们先来看一个案例：这个案例是当我点击按钮时会在中间插入一个f

我们可以确定的是，这次更新对于ul和button是不需要进行更新，需要更新的是我们li的列表

- 在Vue中，对于相同父元素的子元素节点并不会重新渲染整个列表
- 因为对于列表中 a、b、c、d它们都是没有变化的
- 在操作真实DOM的时候，我们只需要在中间插入一个f的li即可

那么Vue中对于列表的更新究竟是如何操作的

- Vue事实上会对于有key和没有key会调用两个不同的方法
- 有key，那么就使用 patchKeyedChildren方法
- 没有key，那么就使用 patchUnkeyedChildren方法

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <ul>
      <li v-for="item in letters" :key="item">{{item}}</li>
    </ul>
    <button @click="insertF">插入F元素</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          letters: ['a', 'b', 'c', 'd']
        }
      },
      methods: {
        insertF() {
          this.letters.splice(2, 0, 'f')
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

#### Vue源码对于key的判断

![](image/Pasted%20image%2020250709153832.png)

#####  没有key的操作

![](image/Pasted%20image%2020250709153912.png)

##### 没有key的过程

我们会发现上面的diff算法效率并不高

- c和d来说它们事实上并不需要有任何的改动
- 但是因为我们的c被f所使用了，所有后续所有的内容都要一次进行改动，并且最后进行新增

![](image/Pasted%20image%2020250709154127.png)

##### 有Key的操作

![](image/Pasted%20image%2020250709155041.png)

##### 有Key的过程

第一步的操作是从头开始进行遍历、比较

- a和b是一致的会继续进行比较
- c和f因为key不一致，所以就会break跳出循环

![](image/Pasted%20image%2020250709155923.png)

第二步的操作是从尾部开始进行遍历、比较

![](image/Pasted%20image%2020250709160008.png)

第三步是如果旧节点遍历完毕，但是依然有新的节点，那么就新增节点：

![](image/Pasted%20image%2020250709230242.png)

第四步是如果新的节点遍历完毕，但是依然有旧的节点，那么就移除旧节点

![](image/Pasted%20image%2020250709230259.png)

第五步是最特色的情况，中间还有很多未知的或者乱序的节点

![](image/Pasted%20image%2020250709230546.png)

所以我们可以发现，Vue在进行diff算法的时候，会尽量利用我们的key来进行优化操作

在没有key的时候我们的效率是非常低效的
在进行插入或者重置顺序的时候，保持相同的key可以让diff算法更加的高效

# Options-API

## 复杂data的处理方式

我们知道，在模板中可以直接通过插值语法显示一些data中的数据

但是在某些情况，我们可能需要对数据进行一些转化后再显示，或者需要将多个数据结合起来进行显示

- 比如我们需要对多个data数据进行运算、三元运算符来决定结果、数据进行某种转化后显示
- 在模板中使用表达式，可以非常方便的实现，但是设计它们的初衷是用于简单的运算
- 在模板中放入太多的逻辑会让模板过重和难以维护
- 并且如果多个地方都使用到，那么会有大量重复的代码

我们有没有什么方法可以将逻辑抽离出去呢？

- 可以，其中一种方式就是将逻辑抽取到一个method中，放到methods的options中
- 但是，这种做法有一个直观的弊端，就是所有的data使用过程都会变成了一个方法的调用
- 另外一种方式就是使用计算属性computed

## 认识计算属性computed

什么是计算属性呢？

- 官方并没有给出直接的概念解释
- 而是说：对于任何包含响应式数据的复杂逻辑，你都应该使用计算属性
- 计算属性将被混入到组件实例中。所有 getter 和 setter 的 this 上下文自动地绑定为组件实例；

计算属性的用法：

- 选项：computed
- 类型：`{ [key: string]: Function | { get: Function, set: Function } }`

## 案例对比

1. 我们有两个变量：firstName和lastName，希望它们拼接之后在界面上显示
2. 我们有一个分数：score
	- 当score大于60的时候，在界面上显示及格
	- 当score小于60的时候，在界面上显示不及格；
3. 我们有一个变量message，记录一段文字：比如Hello World
	- 某些情况下我们是直接显示这段文字
	- 某些情况下我们需要对这段文字进行反转

我们可以有三种实现思路

1. 在模板语法中直接使用表达式
2. 使用method对逻辑进行抽取
3. 使用计算属性computed

### 模板语法

1. 模板中存在大量的复杂逻辑，不便于维护（模板中表达式的初衷是用于简单的计算）
2. 当有多次一样的逻辑时，存在重复的代码
3. 多次使用的时候，很多运算也需要多次执行，没有缓存

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>{{firstName + " " + lastName}}</h2>
    <h2>{{score >= 60 ? '及格': '不及格'}}</h2>
    <h2>{{message.split(" ").reverse().join(" ")}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          firstName: "Kobe",
          lastName: "Bryant",
          score: 80,
          message: "Hello World"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### method实现

1. 我们事实上先显示的是一个结果，但是都变成了一种方法的调用
2. 多次使用方法的时候，没有缓存，也需要多次计算

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>{{getFullName()}}</h2>
    <h2>{{getResult()}}</h2>
    <h2>{{getReverseMessage()}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          firstName: "Kobe",
          lastName: "Bryant",
          score: 80,
          message: "Hello World"
        }
      },
      methods: {
        getFullName() {
          return this.firstName + " " + this.lastName;
        },
        getResult() {
          return this.score >= 60 ? "及格": "不及格";
        },
        getReverseMessage() {
          return this.message.split(" ").reverse().join(" ");
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### computed实现

- 注意：计算属性看起来像是一个函数，但是我们在使用的时候不需要加()，这个后面写setter和getter时会写到
- 我们会发现无论是直观上，还是效果上计算属性都是更好的选择
- 并且计算属性是有缓存的

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>{{fullName}}</h2>
    <h2>{{result}}</h2>
    <h2>{{reverseMessage}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          firstName: "Kobe",
          lastName: "Bryant",
          score: 80,
          message: "Hello World"
        }
      },
      computed: {
        // 定义了一个计算属性叫fullname
        fullName() {
          return this.firstName + " " + this.lastName;
        },
        result() {
          return this.score >= 60 ? "及格": "不及格";
        },
        reverseMessage() {
          return this.message.split(" ").reverse().join(" ");
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

### 计算属性 vs methods

在上面的实现思路中，我们会发现计算属性和methods的实现看起来是差别是不大的，而且我们多次提到计算属性有缓存的

接下来我们来看一下同一个计算多次使用，计算属性和methods的差异

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <button @click="changeFirstName">修改firstName</button>

    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>
    <h2>{{fullName}}</h2>

    <h2>{{getFullName()}}</h2>
    <h2>{{getFullName()}}</h2>
    <h2>{{getFullName()}}</h2>
    <h2>{{getFullName()}}</h2>
    <h2>{{getFullName()}}</h2>
    <h2>{{getFullName()}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          firstName: "Kobe",
          lastName: "Bryant"
        }
      },
      computed: {
        // 计算属性是有缓存的, 当我们多次使用计算属性时, 计算属性中的运算只会执行一次.
        // 计算属性会随着依赖的数据(firstName)的改变, 而进行重新计算.
        fullName() {
          console.log("computed的fullName中的计算");
          return this.firstName + " " + this.lastName;
        }
      },
      methods: {
        getFullName() {
          console.log("methods的getFullName中的计算");
          return this.firstName + " " + this.lastName;
        },
        changeFirstName() {
          this.firstName = "Coder"
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

这是什么原因

- 这是因为计算属性会基于它们的依赖关系进行缓存
- 在数据不发生变化时，计算属性是不需要重新计算的
- 但是如果依赖的数据发生变化，在使用时，计算属性依然会重新进行计算

## 计算属性的setter和getter

计算属性在大多数情况下，只需要一个getter方法即可，所以我们会将计算属性直接写成一个函数。

但是，如果我们确实想设置计算属性的值

- 这个时候我们也可以给计算属性设置一个setter的方法

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <button @click="changeFullName">修改fullName</button>
    <h2>{{fullName}}</h2>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          firstName: "Kobe",
          lastName: "Bryant"
        }
      },
      computed: {

        // fullName 的 getter方法
        fullName() {
          return this.firstName + " " + this.lastName;
        },
        
        // fullName的getter和setter方法
        fullName: {
          get: function() {
            return this.firstName + " " + this.lastName;
          },
          set: function(newValue) {
            console.log(newValue);
            const names = newValue.split(" ");
            this.firstName = names[0];
            this.lastName = names[1];
          }
        }
      },
      methods: {
        changeFullName() {
          this.fullName = "Coder Why";
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## 源码如何对setter和getter处理

你可能觉得很奇怪，Vue内部是如何对我们传入的是一个getter，还是说是一个包含setter和getter的对象进行处理的

- 事实上非常的简单，Vue源码内部只是做了一个逻辑判断而已

![](image/Pasted%20image%2020250709235844.png)

## 认识侦听器watch

什么是侦听器呢？

- 开发中我们在data返回的对象中定义了数据，这个数据通过插值语法等方式绑定到template中
- 当数据变化时，template会自动进行更新来显示最新的数据
- 但是在某些情况下，我们希望在代码逻辑中监听某个数据的变化，这个时候就需要用侦听器watch来完成了

侦听器的用法如下

- 选项：watch
- 类型：`{ [key: string]: string | Function | Object | Array}`

## 侦听器案例

举个例子

- 比如现在我们希望用户在input中输入一个问题
- 每当用户输入了最新的内容，我们就获取到最新的内容，并且使用该问题去服务器查询答案\
- 那么，我们就需要实时的去获取最新的数据变化

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    您的问题: <input type="text" v-model="question">
    <!-- <button @click="queryAnswer">查找答案</button> -->
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          // 侦听question的变化时, 去进行一些逻辑的处理(JavaScript, 网络请求)
          question: "Hello World",
          anwser: ""
        }
      },
      watch: {
        // question侦听的data中的属性的名称
        // newValue变化后的新值
        // oldValue变化前的旧值
        question: function(newValue, oldValue) {
          console.log("新值: ", newValue, "旧值", oldValue);
          this.queryAnswer();
        }
      },
      methods: {
        queryAnswer() {
          console.log(`你的问题${this.question}的答案是哈哈哈哈哈`);
          this.anwser = "";
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

## 侦听器watch的配置选项

我们先来看一个例子

- 当我们点击按钮的时候会修改info.name的值
- 这个时候我们使用watch来侦听info，可以侦听到吗？答案是不可以

这是因为默认情况下，watch只是在侦听info的引用变化，对于内部属性的变化是不会做出响应的

- 这个时候我们可以使用一个选项deep进行更深层的侦听
- 注意前面我们说过watch里面侦听的属性对应的也可以是一个Object

还有另外一个属性，是希望一开始的就会立即执行一次：

- 这个时候我们使用immediate选项
- 这个时候无论后面数据是否有变化，侦听的函数都会有限执行一次

```vue
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
</head>
<body>
  
  <div id="app"></div>

  <template id="my-app">
    <h2>{{info.name}}</h2>
    <button @click="changeInfo">改变info</button>
    <button @click="changeInfoName">改变info.name</button>
    <button @click="changeInfoNbaName">改变info.nba.name</button>
  </template>

  <script src="../js/vue.js"></script>
  <script>
    const App = {
      template: '#my-app',
      data() {
        return {
          info: { name: "why", age: 18, nba: {name: 'kobe'} }
        }
      },
      watch: {
        // 默认情况下我们的侦听器只会针对监听的数据本身的改变(内部发生的改变是不能侦听)
        // info(newInfo, oldInfo) {
        //   console.log("newValue:", newInfo, "oldValue:", oldInfo);
        // }

        // 深度侦听/立即执行(一定会执行一次)
        info: {
          handler: function(newInfo, oldInfo) {
            console.log("newValue:", newInfo.nba.name, "oldValue:", oldInfo.nba.name);
          },
          deep: true, // 深度侦听
          // immediate: true // 立即执行
        }
      },
      methods: {
        changeInfo() {
          this.info = {name: "kobe"};
        },
        changeInfoName() {
          this.info.name = "kobe";
        },
        changeInfoNbaName() {
          this.info.nba.name = "james";
        }
      }
    }

    Vue.createApp(App).mount('#app');
  </script>
</body>
</html>
```

