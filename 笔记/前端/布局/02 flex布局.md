![](image/Pasted%20image%2020230908224146.png)

![](image/Pasted%20image%2020230908224217.png)

![](image/Pasted%20image%2020230908224224.png)

## 主轴与交叉轴

![](image/Pasted%20image%2020230909101935.png)

## flex容器


![](image/Pasted%20image%2020230909102505.png)

### 改变轴方向 flex-direction

![](image/Pasted%20image%2020230909102729.png)

### 换行与缩写 flex-wrap flex-flow

![](image/Pasted%20image%2020230909103700.png)

![](image/Pasted%20image%2020230909103639.png)

### 主轴对齐 justify-content

![](image/Pasted%20image%2020230909103842.png)

### 交叉轴对齐 align-items align-content

- 以一行对齐，不折行也会生效
- 默认值是：如果子元素未设置高度或者高度为auto，将占满整个容器的高度。
- baseline是以X字母下基线对齐

![](image/Pasted%20image%2020230909104925.png)

- 当不允许折行时，align-content是不生效的，只有一行垂直方向不起作用
![](image/Pasted%20image%2020230909104435.png)

## flex子项

### flex-order

- 优先级越高排的越后

![](image/Pasted%20image%2020230910145925.png)

### flex-grow扩展比例

 - 这个参数是对剩余横向空间进行分配，默认是0
 - 如果大于1，且当前只有一个元素设置这个值，那么就会填充剩余的空间，如果有多个元素设置这个值，则会按比例分配
 - 如果小于一，也是按照比例分配

![](image/Pasted%20image%2020230910145609.png)

### flex-shrink收缩比例

- 空间不足时默认收缩，容器大小和父容器大小相同
- 如果数值小于1，则收缩时将溢出的部分按比例收缩
- 复杂的是多个元素，以及宽度都不相同，也是按照溢出比例分配收缩
![](image/Pasted%20image%2020230910145847.png)

### flex-basis和flex缩写

- flex-basis 优先级大于宽度/高度
- 这个属性会被父容器设置的flex-direction所影响，因为这个属性设置主轴的大小
- 可以更加方便的设置元素的方向，就不需要调整主轴方向后通过JS设置容器大小
- 0% auto 100px 100%

![](image/Pasted%20image%2020230910151029.png)

```css
flex-grow: 1
flex-shrink: 1;
flex-basis: 0%; 
flex:1;

flex-grow: 0;
flex-shrink: 1;
flex-basis: 0%;
flex:0;

flex-grow: 1;
flex-shrink: 1;
flex-basis: auto;
flex:auto;

flex-grow: 1;
flex-shrink: 0;
flex-basis: 50%;
flex:1 0 50%;
```
### align-self

- 也就是align-item针对某个子元素单独设置
- 默认是和父容器中设置的align-item值一样

![](image/Pasted%20image%2020230910153336.png)
## 内联与块的垂直居中布局

![](image/Pasted%20image%2020230909122108.png)

### 内联

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    1111  
</div>  
</body>  
<style>  
.box {  
        border: 1px black solid;  
        background-color: pink;  
        height: 300px;  
        width: 300px;  
        display: flex;  
        align-items: center;  
        justify-content: space-evenly;  
    }    
</style>
```

### 块

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>test</div>  
    <div>test</div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        border: 1px black solid;  
        background-color: pink;  
        height: 300px;  
        width: 300px;  
        display: flex;  
        align-items: center;  
        justify-content: space-evenly;  
  
    }  
  
    .box div {  
        background-color: blue;  
        width: 100px;  
        height: 50px;  
        color: aliceblue;  
        display: flex;  
        align-items: center;  
        justify-content: center;  
    }  
</style>
```

## 不定项居中布局

![](image/Pasted%20image%2020230909125033.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
    <div>4</div>  
    <div>5</div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        border: 1px black solid;  
        background-color: blue;  
        height: 150px;  
        width: 300px;  
        display: flex;  
        align-items: flex-end;  
        justify-content: center;  
  
    }  
  
    .box div {  
        background-color: pink;  
        width: 30px;  
        height: 30px;  
        border-radius: 50%;  
        color: black;  
        display: flex;  
        align-items: center;  
        justify-content: center;  
        margin: 10px;  
  
    }  
</style>
```

## 均分项布局

![](image/Pasted%20image%2020230909203849.png)

- 最两边是固定宽度，不是变动的

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        border: 1px black solid;  
        background-color: blue;  
        height: 300px;  
        display: flex;  
        align-items: flex-end;  
        justify-content: space-between;  
        padding: 0 20px;  
    }  
  
    .box div {  
        background-color: pink;  
        width: 30px;  
        height: 30px;  
        border-radius: 50%;  
        color: black;  
        display: flex;  
        align-items: center;  
        justify-content: center;  
    }  
</style>
```

## 子项分组布局

![](image/Pasted%20image%2020230909212158.png)

- 第一种（不太方便）

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>  
        <div>1</div>  
    </div>  
    <div>  
        <div class="item">2</div>  
        <div >3</div>  
    </div>  
  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        background-color: skyblue;  
        height: 200px;  
        display: flex;  
        justify-content: space-between;  
        align-items: center;  
    }  
  
    .box div {  
        display: flex;  
    }  
  
    .box div div {  
        width: 100px;  
        height: 50px;  
        background-color: pink;  
    }  
  
    .item {  
        margin-right: 20px;  
    }  
  
  
</style>  
</html>
```

- 第二种（简单方法使用了auto）

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
    <div>4</div>  
    <div>5</div>  
    <div>6</div>  
    <div>7</div>  
    <div>8</div>  
    <div>9</div>  
  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        background-color: skyblue;  
        height: 200px;  
        display: flex;  
        align-items: center;  
    }  
  
    .box div {  
        width: 60px;  
        height: 40px;  
        margin-right: 10px;  
        background-color: pink;  
    }  
  
    .box div:nth-of-type(3) {  
        /* 自动填充剩下的位置*/  
        margin-right: auto;  
    }  
  
    .box div:nth-of-type(7) {  
        /* 自动填充剩下的位置*/  
        margin-right: auto;  
    }  
</style>  
</html>
```

## 等高布局

![](image/Pasted%20image%2020230910153914.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
    </div>  
    <div>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
    </div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    .box {  
        background-color: skyblue;  
        width: 500px;  
        display: flex;  
        justify-content: space-between;  
    }  
  
    .box div {  
        width: 100px;  
        background-color: pink;  
  
    }  
  
</style>  
</html>
```

## 两列与三列布局

![](image/Pasted%20image%2020230910160151.png)

### 两列

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div class="col-left">  
  
    </div>  
    <div class="col-right">  
  
    </div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    body {  
        margin: 0;  
    }  
  
    .box {  
        background-color: skyblue;  
        height: 100vh;  
        display: flex;  
    }  
  
    .col-left {  
        width: 300px;  
        background: pink;  
  
    }  
  
    .col-right {  
        flex-grow: 1;  
        background: bisque;  
    }  
  
</style>  
</html>
```

### 三列

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div class="col-left">  
    </div>  
    <div class="col-middle">  
    </div>  
    <div class="col-right"></div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    body {  
        margin: 0;  
    }  
  
    .box {  
        background-color: skyblue;  
        height: 100vh;  
        display: flex;  
    }  
  
    .col-left {  
        width: 300px;  
        background: pink;  
  
    }  
  
    .col-middle {  
        flex-grow: 1;  
        background: bisque;  
    }  
  
    .col-right {  
        width: 200px;  
        background-color: tomato;  
    }  
  
</style>  
</html>
```

## Sticky Footer布局

![](image/Pasted%20image%2020230910194215.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div class="header">  
        <p>我是header</p>  
    </div>  
    <div class="content">  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
        <p>测试内容</p>  
    </div>  
    <div class="footer">  
        <p>我是footer</p>  
    </div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    body {  
        margin: 0;  
    }  
  
    .box {  
        background-color: skyblue;  
        min-height: 100vh;  
        display: flex;  
        flex-direction: column;  
    }  
  
    .header {  
        height: 100px;  
        background: pink;  
  
    }  
  
    .content {  
        flex-grow: 1;  
        background: bisque;  
    }  
  
    .footer {  
        height: 100px;  
        background-color: tomato;  
    }  
  
</style>  
</html>
```

## 溢出项布局

![](image/Pasted%20image%2020230910195029.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <title>Title</title>  
</head>  
<body>  
<div class="box">  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
    <div>4</div>  
    <div>5</div>  
    <div>6</div>  
    <div>7</div>  
    <div>8</div>  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
    <div>4</div>  
    <div>5</div>  
    <div>6</div>  
    <div>7</div>  
    <div>8</div>  
    <div>1</div>  
    <div>2</div>  
    <div>3</div>  
    <div>4</div>  
    <div>5</div>  
    <div>6</div>  
    <div>7</div>  
    <div>8</div>  
</div>  
</body>  
<style>  
    /* 代码编写区域 */    body {  
        margin: 0;  
    }  
  
    .box {  
        background-color: skyblue;  
        height: 100px;  
        display: flex;  
        align-items: center;  
    }  
  
    .box div {  
        background-color: pink;  
        width: 100px;  
        height: 80px;  
        margin-right: 10px;  
        flex-shrink: 0;  
    }  
  
  
</style>  
</html>
```

## 综合案例-轮播图

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="./iconfont.css">
    <link rel="stylesheet" href="./reset.css">
    <style>
        .swiper-container{
            position: relative;
        }
        .swiper-wrapper{
            display: flex;
        }
        /*溢出盒布局*/
        .swiper-slide{
            width:100%;
            flex-shrink: 0;
        }
        /*每一个图片都占满设备*/
        .swiper-slide img{
            width:100%;
        }
        /*采用绝对定位，内部元素采用flex布局*/
        .swiper-pagination{
            position: absolute;
            height: 28px;
            width: 100%;
            bottom:0;
            display: flex;
            justify-content: center;
            align-items: center;
        }
        /*采用内联盒子，并且设置圆角和颜色*/
        .swiper-pagination-bullet{
            width:8px;
            height:8px;
            border-radius: 50%;
            background:#c6bcaf;
            margin:0 4px;
        }
        /*被选中的样式*/
        .swiper-pagination-bullet-active{
            background:white;
        }
        /*采用绝对定位，flex布局，高度和大小和父容器一样*/
        .swiper-button-prev, .swiper-button-next{
            position: absolute;
            top:0;
            height:100%;
            display: flex;
            align-items: center;
        }
        .swiper-button-prev{
            left:0;
        }
        .swiper-button-next{
            right:0;
        }
        /*设置特殊字符大小*/
        .swiper-button-prev i, .swiper-button-next i{
            font-size:44px;
            color:white;
        }
    </style>
</head>
<body>
    <div class="swiper-container">
        <div class="swiper-wrapper">
            <div class="swiper-slide"><img src="https://pic3.iqiyipic.com/common/lego/20210609/e66f0e28608f4aa7b08b5d93088c73c6.jpg?caplist=jpg,webp" alt=""></div>
            <div class="swiper-slide"><img src="https://pic0.iqiyipic.com/common/lego/20210614/71f0084bddcb446db323fa9eebf53585.jpg?caplist=jpg,webp" alt=""></div>
            <div class="swiper-slide"><img src="https://m.iqiyipic.com/common/lego/20210613/80bfb766ac36470f9ec3a3788f85eabe.jpg?caplist=jpg,webp" alt=""></div>
        </div>
        <!-- 如果需要分页器 -->
        <div class="swiper-pagination">
            <span class="swiper-pagination-bullet swiper-pagination-bullet-active"></span>
            <span class="swiper-pagination-bullet"></span>
            <span class="swiper-pagination-bullet"></span>
        </div>
        
        <!-- 如果需要导航按钮 -->
        <div class="swiper-button-prev">
            <i class="iconfont icon-swiperhoutui"></i>
        </div>
        <div class="swiper-button-next">
            <i class="iconfont icon-swiperqianjin"></i>
        </div>
    </div>
</body>
</html>
```

## 综合案例-知乎导航

![](image/Pasted%20image%2020230910205834.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="./iconfont.css">
    <link rel="stylesheet" href="./reset.css">
    <style>
        body{
            background:#f6f6f6;
        }
        .header-container{
            background:#ffffff;
        }
        .header-wrapper{
            /*居中*/
            margin:0 auto;
            height: 52px;
            /*设置最大最小宽度，避免文字错位*/
            min-width:1000px;
            max-width:1156px;
            display: flex;
            /*这个是设置子元素垂直居中*/
            align-items: center;
        }
        .header-logo{
            /*与文字空出间隔*/
            margin-right: 40px;
        }
        .header-nav{
            /*采用flex布局，让子元素横向排列*/
            display: flex;
        }
        .header-nav li{
            margin-right:30px;
        }
        .header-search{
            /*父容器自适应空余宽度*/
            flex-grow:1;
            display: flex;
            /*内部子元素水平居中，方便扩展，内部子元素限制最大宽度*/
            justify-content: center;
        }
        .header-search-wrapper{
            max-width:482px;
            height:34px;
            flex-grow: 1;
            display: flex;
            /*内部的input 和 i 都垂直居中*/
            align-items:center;
            /*在两侧平分空间*/
            justify-content: space-between;
            background:#f6f6f6;
            border-radius: 100px;
        }
        .header-search-input{
            border:none;
            height: 34px;
            /*自动填充*/
            flex-grow: 1;
            background:none;
            margin:0 20px;
        }
        .header-search-wrapper i{
            /*文字垂直居中*/
            line-height: 34px;
            height: 34px;
            margin: 0 10px;:
        }
        .header-btn{
            /*将内部的按钮转成块元素后通过flex布局*/
            display: flex;
        }
        .header-btn-login{
            width:60px;
            height:32px;
            border:1px #0066ff solid;
            border-radius: 3px;
            color:#0066ff;
            background:none;
            cursor: pointer;
            /*因为内联元素存在空隙，于是转成块元素进行排列*/
            display: block;
            margin-left:20px;
        }
        .header-btn-zhihu{
            width:90px;
            height:32px;
            background:#0066ff;
            color:white;
            border:none;
            border-radius: 3px;
            /*因为内联元素存在空隙，于是转成块元素进行排列*/
            display: block;
            margin-left:20px;
            cursor: pointer;
        }
    </style>
</head>
<body>
    <div class="header-container">
        <div class="header-wrapper">
            <div class="header-logo">
                <a href="#"><img src="./logo.png" alt=""></a>
            </div>
            <ul class="header-nav">
                <li>首页</li>
                <li>会员</li>
                <li>发现</li>
                <li>等你来答</li>
            </ul>
            <div class="header-search">
                <div class="header-search-wrapper">
                    <input class="header-search-input" type="text" placeholder="520文案">
                    <i class="iconfont icon-fangdajing"></i>
                </div>
            </div>
            <div class="header-btn">
                <button class="header-btn-login">登录</button>
                <button class="header-btn-zhihu">加入知乎</button>
            </div>
        </div>
    </div>
</body>
</html>
```