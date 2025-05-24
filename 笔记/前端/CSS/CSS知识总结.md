# 编写样式

## 内联样式

```html
<!-- 内联样式(inline) -->  
<div style="color: red; font-size: 30px;">我是div元素</div>
```

## 选择器

```css
/* 找到class为.div-one的元素 */
.div-one {  
  color: red;   
  font-size: 30px;   
  background-color: orange;  
}

<div class="div-one">我是div元素</div>  
<div>我也是div元素</div>
```

## link

```css
<link rel="stylesheet" href="./css/style.css">  
<link rel="stylesheet" href="./css/test.css">
```

## @import

```css
/* 可以通过@import引入其他的css资源 */
@import url(./style.css);  
@import url(./test.css);
```

# 文档和补充

## W3C官方地址

[CSS官方文档地址](https://www.w3.org/TR/?tags%5B0%5D=css)

## CSS推荐文档地址

[CSS推荐文档地址](https://developer.mozilla.org/zh-CN/docs/Web/CSS)

## 浏览器兼容查询

[浏览器兼容查询](https://caniuse.com/)

## link 元素

link元素是外部资源链接元素，规范了文档与外部资源的关系，通常是在head元素中，此外也可以被用来创建站点图标（比如 “favicon” 图标）。

[rel属性列表](https://developer.mozilla.org/zh-CN/docs/Web/HTML/Reference/Attributes/rel)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>京东(JD.COM)-正品低价、品质保障、配送及时、轻松购物！</title>  
  <!-- 引入css -->  
  <link rel="stylesheet" href="./css/style.css">  
  <!-- 引入icon(站点的图标) -->  
  <link rel="icon" href="../images/favicon.ico">  
</head>  
<body>  
  </body>  
</html>
```

## vertical-align

`vertical-align` 属性用来指定行内（inline）、行内区块（inline-block）、表格单元格（table-cell）盒子的垂直对齐方式

![](image/Pasted%20image%2020250524150842.png)

### 深入理解 line-box

![](image/Pasted%20image%2020250524152657.png)

 官方文档中 vertical-align 会影响 行内块级元素 在一个 行盒 中垂直方向的位置

思考：一个div没有设置高度的时候，会不会有高度

- 没有内容，没有高度
- 有内容，内容撑起来高度

是内容撑起来高度的本质是什么呢

- 内容有行高（line-height），撑起来了div的高度，这个涉及到之后笔记中的 BFC 和 IFC

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 当前box有没有高度: 会有高度 */
    /* 为什么有高度: 由内容的撑起来 */
    /* 本质: 内容的行高撑起来 */
    .box {
      background-color: orange;
    }

    .small {
      display: inline-block;
      width: 100px;
      height: 100px;
      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="box">
    我是div元素 <span class="small"></span>
    虽然说，现在想吃什么用什么海外产品，都能代购，但是自己去购买，感觉还是不同。
    一个人在路上，心情也会不同，路上的行程，可以听书看书，到达后，疯狂的游玩。书的种类很多，旅行的书本真的不少，常常看到人们去各地游玩，自己心中也跟着想去。有时间，可以试着一个人去旅行，那是一种享受一种幸福。女人不必限制于单身生活，才会各地旅行，婚后的女性，有时间，也可以一个人去旅行，那是一种不同的感受，有些人也可以带小孩老公一起去旅行。独自游玩是一种幸福，家庭一起去旅行，也是一种幸福。单身的女性，可以一个人独游。婚后的女性，也可以一个人独游。当然，婚后若是自己一个人不方便，那就全家人旅行。
  </div>

</body>
</html>
```

行高为什么可以撑起div的高度

- 这是因为 line boxes 的存在，并且 line-boxes 有一个特性，包裹每行的 inline level 
- 而其中的文字是有行高的，必须将整个行高包裹进去，才算包裹这个 line-level 

那么，进一步思考：

- 如果这个div中有图片，文字，inline-block，甚至他们设置了margin这些属性呢？

### 不同情况分析

1. 只有文字时，line boxes 如何包裹内容？（注意：红色是包裹的div，下面也都一样）

![](image/Pasted%20image%2020250524153130.png)

2. 有图片，有文字时，line-boxes如何包裹内容

![](image/Pasted%20image%2020250524153202.png)

3. 有图片，有文字，有inline-block（比图片要大）如何包裹内容

![](image/Pasted%20image%2020250524153218.png)

4. 有图片，有文字，有inline-block（比图片要大）而且设置了margin-bottom，如何包裹内容

![](image/Pasted%20image%2020250524153238.png)

5. 情况五：有图片、文字、inline-block（比图片要大）而且设置了margin-bottom并且有文字，如何包裹内容？

![](image/Pasted%20image%2020250524153259.png)

### vertical-align 的 baseline

结论：line-boxes一定会想办法包裹住当前行中所有的内容。

但是，但是为什么对齐方式千奇百怪呢？

- 你认为的千奇百怪，其实有它的内在规律
- 答案就是baseline对齐

我们来看官方 vertical-align 的默认值：没错，就是 baseline

但是 baseline 都是谁呢？

- 文本的 baseline 是字母x的下方
- Inline-block 默认的 baseline 是 margin-bottom 的底部（没有，就是盒子的底部）
- Inline-block 有文本时，baseline 是最后一行文本的 x 的下方

一切都解释通了

### vertical-align的其他值

现在，对于不同的取值就非常容易理解了

- baseline(默认值)：基线对齐（你得先明白什么是基线）
- top：把行内级盒子的顶部跟line boxes顶部对齐
- middle：行内级盒子的中心点与父盒基线加上x-height一半的线对齐
- bottom：把行内级盒子的底部跟line box底部对齐
- `<percentage>`：把行内级盒子提升或者下降一段距离（距离相对于line-height计算\元素高度） 0%意味着同baseline一样
- `<length>`：把行内级盒子提升或者下降一段距离，0cm意味着同baseline一样

解决图片下边缘的间隙方法:

- 方法一: 设置成top/middle/bottom
- 方法二: 将图片设置为block元素

## BFC

## Emmet 语法

### 了解 Emmet 语法

Emmet (前身为 Zen Coding) 是一个能大幅度提高前端开发效率的一个工具

- 在前端开发的过程中，一大部分的工作是写 HTML、CSS 代码, 如果手动来编写效果会非常低
- VsCode内置了Emmet语法,在后缀为 .html / .css中输入缩写后按 Tab / Enter 键即会自动生成相应代码

! 和 html:5 可以快速生成完整结构的 html5 代码

### `>` （子代） `+`（兄弟）

![](image/Pasted%20image%2020250521102748.png)

### `*` （多个） `^`（上一级）

![](image/Pasted%20image%2020250521102809.png)

### `()` （分组）

![](image/Pasted%20image%2020250521102827.png)

### 属性(id属性、class属性、普通属性) {}（内容）

![](image/Pasted%20image%2020250521102842.png)

### `$` （数字）

![](image/Pasted%20image%2020250521102854.png)

### 隐式标签

![](image/Pasted%20image%2020250521102914.png)

### CSS Emmet

![](image/Pasted%20image%2020250521102929.png)

# CSS属性

## 文本

### reset.css

```css
a {  
  text-decoration: none;  
}
```

### text-decoration

text-decoration用于设置文字的装饰线

text-decoration有如下常见取值

- none：无任何装饰线，可以去除a元素默认的下划线
- underline：下划线
- overline：上划线
- line-through：中划线（删除线）

a元素有下划线的本质是被添加了text-decoration属性

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <link rel="stylesheet" href="./css/reset.css">  
  <style>  
    .baidu {  
      text-decoration: underline;  
      cursor: pointer;  
    }  
  
    .google {  
      text-decoration: line-through;  
  
      /* 设置文本的颜色(前景色) */  
      color: red;  
    }  
  
    .bing {  
      text-decoration: overline;  
    }  
  
    a {  
      text-decoration: none;  
    }  
  </style>  
</head>  
<body>  
  <!-- a元素默认有添加text-decoration -->  
  <a href="http://www.baidu.com">百度一下</a>  
  
  <!-- span元素也添加装饰线 -->  
  <span class="baidu">百度一下</span>  
  
  <!-- 装饰线其他的值 -->  
  <span class="google">Google一下</span>  
  <span class="bing">必应一下</span>  
  
  <a href="http://www.taobao.com">淘宝一下</a>  
  
</body>  
</html>
```

### text-transform

text-transform用于设置文字的大小写转换

text-transform有几个常见的值
 
 - capitalize：(使…首字母大写, 资本化的意思)将每个单词的首字符变为大写
 - uppercase：(大写字母)将每个单词的所有字符变为大写
 - lowercase：(小写字母)将每个单词的所有字符变为小写
 - none：没有任何影响

实际开发中用JavaScript代码转化的更多.

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .info {  
      /* text-transform: capitalize; */  
      /* text-transform: uppercase; */      text-transform: lowercase;  
    }  
  </style>  
</head>  
<body>  
  <div class="info">my name is han, AGE IS 18</div>  
  
</body>  
</html>
```

### text-indent

text-indent用于设置第一行内容的缩进

```css
text-indent: 2em;  // 刚好是缩进2个文字
```

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    p {  
      font-size: 40px;  
  
      /* em: 相对于字体的大小 */      
      text-indent: 2em;  
    }  
  </style>  
</head>  
<body>  
  <h2>标题</h2>  
  <p>  
    如果说1号公路环岛之旅是行走冰岛的经典路线，与动物为伴的生态游则是深入了解冰岛的“最佳打卡方式”。在人类踏足冰岛前，这片火山地区几乎没有陆地动物存在，唯一的例外就是北极狐。这种小型哺乳动物周身包裹着厚厚的皮毛，可以在最后一个冰河时期结束前穿越冰封的海洋，抵达冰岛安家，成为这里唯一的原生陆地哺乳动物。直到后来有人类踏上冰岛，兔子、羊、马、鹿等哺乳动物才走进了冰岛的生态系统。比如冰岛马，它们在1000多年前从挪威跟随冰岛第一批定居者来到冰岛并繁衍生存下来。成年冰岛马体型矮小，会被人误会为小马驹，但实际上冰岛马步伐稳健，善于行走在崎岖地带，哪怕是初学者也可驾驭，骑着冰岛马旅游已成为当地颇受欢迎的旅游项目。  
  </p>  
  
</body>  
</html>
```

### text-align

text-align: 直接翻译过来设置文本的对齐方式;

定义行内内容（例如文字）如何相对它的块父元素对齐;

The `text-align` [CSS](https://developer.mozilla.org/en-US/docs/Web/CSS) property sets the horizontal alignment of the **inline-level content** inside a block element or table-cell box. This means it works like [`vertical-align`](https://developer.mozilla.org/en-US/docs/Web/CSS/vertical-align) but in the horizontal direction.

常用的值
- left：左对齐
- right：右对齐
- center：正中间显示
- justify：两端对齐

#### 基本使用

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      background-color: #f00; /* #FF0000 => rgb(255, 0, 0) */  
      color: white;  
  
      /* text-align */  
      text-align: center;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  
</body>  
</html>
```

#### 图像居中

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      background-color: #f00;  
      height: 300px;  
  
      /* 让图片居中显示 */      
      text-align: center;  
    }  
  
    img {  
      width: 200px;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    <img src="../images/gouwujie01.jpg" alt="">  
  </div>  
  
</body>  
</html>
```

#### 块级元素

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      background-color: #f00;  
      height: 300px;  
  
      text-align: center;  
    }  
  
    .content {  
      background-color: #0f0;  
      height: 200px;  
      width: 200px;  
  
      /* display: inline-block; */  
      margin: 0 auto;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    <div class="content"></div>  
  </div>  
  
</body>  
</html>
```

#### justify

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      width: 200px;  
      background-color: #f00;  
      color: white;  
  
      text-align: justify;  
      text-align-last: justify;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    This CSS module defines properties for text manipulation and specifies their processing model. It covers line breaking, justification and alignment, white space handling, and text transformation. why  
  </div>  
  
</body>  
</html>
```

### word/letter-spacing

letter-spacing、word-spacing分别用于设置字母、单词之间的间距

- 默认是0，可以设置为负数

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      /* letter-spacing: 10px; */  
      word-spacing: 30px;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">my name is han</div>  
  
</body>  
</html>
```

## 字体

### font-size

font-size 决定文字的大小

常用的设置

- 具体数值+单位

	- 比如 100 px

- 也可以使用em单位(不推荐)

	- 1em 代表 100%
	- 2 em 代表 200%
	- 0.5 em 代表 50%

- 百分比

	-基于父元素的font-size计算，比如 50% 表示等于父元素 font-size 的一半

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* 继承先略过 */    .home {  
      font-size: 20px;  
    }  
  
    .box {  
      /* 字体设置的方式一: px */  
      /* font-size: 50px; */      /* 了解: em -> 父元素的字体的尺寸 */  
      /* 字体设置的方式二: em */  
      /* font-size: 2em; */  
      /* 字体设置的方式三: 百分比% */  
      font-size: 200%;  
    }  
  </style>  
</head>  
<body>  
  <div class="home">  
    <div class="box">我是div元素</div>  
  </div>  
  
  <div class="box1">我是div元素</div>  
  
</body>  
</html>
```

### font-family

 font-family用于设置文字的字体名称
 
 - 可以设置1个或者多个字体名称
 - 浏览器会选择列表中第一个该计算机上有安装的字体
 - 或者是通过 @font-face 指定的可以直接下载的字体。

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <link rel="stylesheet" href="./css/base.css">  
  <style>  
      </style>  
</head>  
<body>  
  </body>  
</html>
```

```css
body {  
  font-family: "Microsoft YaHei", "Heiti SC", tahoma, arial, "Hiragino Sans GB", "\5B8B\4F53", sans-serif;  
}
```

### font-weight

 font-weight用于设置文字的粗细（重量）
 - 常见的取值
 - 每一个数字表示一个重量
 - 100 | 200 | 300 | 400 | 500 | 600 | 700 | 800 | 900
 - normal：等于 400
 - bold：等于 700
 - strong、b、h1 ~ h6 等标签的 font-weight 默认就是 bold

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      /* font-weight: bold; */  
      font-weight: 700;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  <div>我是div元素</div>  
  
</body>  
</html>
```

### font-style

font-style用于设置文字的常规、斜体显示

- normal：常规显示
- italic(斜体)：用字体的斜体显示(通常会有专门的字体)
- oblique(倾斜)：文本倾斜显示(仅仅是让文字倾斜)
- em、i 等元素的font-style默认就是italic

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      /* 斜体: 字体本身支持斜体时, 显示的斜体 */      /* font-style: italic; */      /* 倾斜: 让文本进行倾斜 */      font-style: oblique;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  <div>我是div元素</div>  
  
</body>  
</html>
```

### font-variant

 font-variant可以影响小写字母的显示形式
 
 - variant是变形的意思

- 可以设置的值如下
	- normal：常规显示
	- small-caps：将小写字母替换为缩小过的大写字母

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      font-variant: small-caps;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">My Name Is Coderwhy</div>  
  
</body>  
</html>
```

### line-height

line-height用于设置文本的行高

- 行高可以先简单理解为一行文字所占据的高度
- 行高的严格定义是：两行文字基线（baseline）之间的间距
- 基线（baseline）：与小写字母x最底部对齐的线

注意区分height和line-height的区别

- height：元素的整体高度
- line-height：元素中每一行文字所占据的高度
- 应用实例：假设div中只有一行文字，如何让这行文字在div内部垂直居中
	- 让line-height等同于height

![](image/Pasted%20image%2020250519220749.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      height: 100px;  
      background-color: #f00;  
      color: #fff;  
  
      line-height: 100px;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  
</body>  
</html>
```

### font

 font是一个缩写属性

- font 属性可以用来作为 font-style, font-variant, font-weight, font-size, line-height 和 font-family 属性的简写;
- font-style font-variant font-weight font-size/line-height font-family
- 规则
	- font-style、font-variant、font-weight可以随意调换顺序，也可以省略
	- line-height可以省略，如果不省略，必须跟在font-size后面
	- font-size、font-family不可以调换顺序，不可以省略

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      /* 关于字体的属性 */      
      font-size: 30px;  
      font-weight: 700;  
      font-variant: small-caps;  
      font-style: italic;  
      font-family: serif;  
      line-height: 30px;  
  
      /* 缩写属性 */      /* 1.5的行高是相对于font-size的 */      
      font: italic small-caps 700 30px/1.5 serif;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  
</body>  
</html>
```

## 背景

在开发中, 为了让网页更加美观, 我们经常会设置各种各样的背景

- 这里我们要学习设置背景的更多知识

### background-image

background-image用于设置元素的背景图片

- 会盖在(不是覆盖)background-color的上面

如果设置了多张图片

- 设置的第一张图片将显示在最上面，其他图片按顺序层叠在下面

注意：如果设置了背景图片后，元素没有具体的宽高，背景图片是不会显示出来的

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 600px;
      height: 600px;
      background-color: #f00;

      /* 设置背景图片 */
      background-image: url(../images/kobe01.jpg), url(../images/kobe02.png);
      background-repeat: no-repeat;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

![](image/Pasted%20image%2020250521093704.png)

### background-repeat

background-repeat用于设置背景图片是否要平铺

常见的设值有

- repeat：平铺
- no-repeat：不平铺
- repeat-x：只在水平方向平铺
- repeat-y：只在垂直平方向平铺

![](image/Pasted%20image%2020250521093731.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 600px;
      height: 600px;
      background-color: #f00;

      /* 设置背景图片 */
      background-image: url(../images/wall.png);
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

这个图片只是一小块，但是平铺能形成一面墙

![](image/Pasted%20image%2020250521094012.png)

### background-size

background-size 用于设置背景图片的大小

![](image/Pasted%20image%2020250521094556.png)

- auto ：默认值, 以背景图本身大小显示
- cover ：缩放背景图，以完全覆盖铺满元素,可能背景图片部分看不见
- contain ：缩放背景图，宽度或者高度铺满元素，但是图片保持宽高比
- `<percentage>` ：百分比，相对于背景区（background positioning area）
- length ：具体的大小，比如100 px

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 600px;
      height: 600px;
      background-color: #f00;

      /* 设置背景图片 */
      background-image: url(../images/kobe01.jpg);
      background-repeat: no-repeat;

      /* 设置背景的尺寸 */
      /* background-size: 100% 100%; */
      /* background-size: 100px 100px; */
      background-size: 100px auto;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

### background-position

background-position用于设置背景图片在水平、垂直方向上的具体位置

- 可以设置具体的数值 比如 20 px 30 px
- 水平方向还可以设值 ：left、center、right
- 垂直方向还可以设值 ：top、center、bottom
- 如果只设置了1个方向，另一个方向默认是 center

![](image/Pasted%20image%2020250521094835.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 600px;
      height: 600px;
      background-color: #f00;

      /* 设置背景图片 */
      background-image: url(../images/kobe01.jpg);
      background-repeat: no-repeat;

      /* 背景位置 */
      /* background-position: -100px -100px; */
      background-position: top;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      margin: 0;
    }

    .box {
      height: 489px;
      background-color: #f00;

      background-image: url(../images/mhxy.jpg);
      background-position: center;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

### background-attachment

background-attachment决定背景图像的位置是在视口内固定，或者随着包含它的区块滚动

可以设置以下3个值

- scroll ：此关键属性值表示背景相对于元素本身固定， 而不是随着它的内容滚动
- local ：此关键属性值表示背景相对于元素的内容固定。如果一个元素拥有滚动机制，背景将会随着元素的内容滚动.
- fixed ：此关键属性值表示背景相对于视口固定。即使一个元素拥有滚动机制，背景也不会随着元素的内容滚动。

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 300px;
      height: 300px;
      overflow: scroll;
      color: #fff;
      background-color: #f00;

      background-image: url(../images/kobe01.jpg);

      /* 附加效果 */
      /* background-attachment: scroll; */
      /* background-attachment: local; */
      /* background-attachment: fixed; */
    }
  </style>
</head>
<body>
  
  <div class="box">
    赏花游人群中，朋友相约出游、全家出游、亲子出游占比较高。同程旅行大数据显示，赏花游对男性和女性游客同样具有吸引力。在关注赏花游的人群中，男性占比为48%，女性占比为52%，几乎持平。在年龄分布上，80后和90后更爱赏花游，00后赏花游客群体增长迅速，占比从去年的5%增至今年的16%。和朋友一起相约赏花，在赏花人群中占比最高，达到36%，带着家人孩子一起外出赏花的游客占比也达到33%。
    3月上旬，多地出现散发疫情，赏花长线游市场受到较大影响。
    “近两年以来，春季赏花游市场中，周边短途游占比进一步提高，从今年途牛旅游网预订情况看，超七成游客选择周末周边游。疫情发生前，每年春季，江西婺源、西藏林芝等地跟团游中，外省游客占比较大，今年，在跨省游受限的情况下，赏花长线游产品受影响较大。”途牛旅游相关负责人告诉记者。

    驴妈妈旅游网首席执行官邹庆龄说：“今年赏花游目的地更偏向省内、当地，其次是周边省市。从玩法上来看，赏花游产品呈现高频化、深度打卡、网红内容体验等特点；行程设计由单纯的赏花到品农家菜、入住当地酒店及特色民宿，赏花游呈现慢节奏体验的趋势。”
  </div>


  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>

</body>
</html>
```

### background

background 是一系列背景相关属性的简写属性

![](image/Pasted%20image%2020250521101318.png)

background-size 可以省略，如果不省略，/background-size 必须紧跟在 background-position 的后面，其他属性也都可以省略，而且顺序任意

### background-image和img对比

利用background-image和img都能够实现显示图片的需求，在开发中该如何选择？

|               |     img      | background-image |
| :-----------: | :----------: | :--------------: |
|      性质       |   HTML 元素    |      CSS 样式      |
|   图片是否占用空间    |      √       |        ×         |
|  浏览器右键直接查看地址  |      √       |        ×         |
| 支持 CSS Sprite |      ×       |        √         |
|    利于 SEO     | √（结合 alt 属性） |        ×         |

总结

- img，作为网页内容的重要组成部分
	- 广告图片
	- LOGO图片
	- 文章配图
	- 产品图片
- background-image，可有可无
	- 有，能让网页更加美观
	- 无，也不影响用户获取完整的网页内容信息

# CSS 选择器

## 介绍

开发中经常需要找到特定的网页元素进行设置样式

- 什么是CSS选择器
	- 按照一定的规则选出符合条件的元素，为之添加CSS样式

- 选择器的种类繁多，大概可以这么归类

	- 通用选择器（universal selector）
	- 元素选择器（type selectors）
	- 类选择器（class selectors）
	- id选择器（id selectors）
	- 属性选择器（attribute selectors）
	- 组合（combinators）
	- 伪类（pseudo-classes）
	- 伪元素（pseudo-elements）

## 通用选择器

通用选择器（universal selector）

- 所有的元素都会被选中
- 一般用来给所有元素作一些通用性的设置
- 比如内边距、外边距
- 比如重置一些内容
- 效率比较低，尽量不要使用

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* * {  
      font-size: 30px;      background-color: #f00;    } */  
    /* div {      background-color: #f00;    } */  
    /* 更推荐的做法 */    body, p, div, h2, span {  
      margin: 0;  
      padding: 0;  
    }  
  </style>  
</head>  
<body>  
  <div>我是div元素</div>  
  <p>我是p元素</p>  
  
  <div>  
    <h2>我是h2元素</h2>  
    <p>我也是p元素  <span>呵呵呵呵</span> </p>  
  </div>  
  
</body>  
</html>
```

## 简单选择器

简单选择器是开发中用的最多的选择器

- 元素选择器（type selectors）, 使用元素的名称
- 类选择器（class selectors）, 使用 .类名 
- id选择器（id selectors）, 使用 `#id`

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    div {  
      color: red;  
    }  
  
    .box {  
      color: blue;  
    }  
  
    #home {  
      color: green;  
    }  
  </style>  
</head>  
<body>  
  <!-- 强调: 在同一个HTML文档中, id不要重复, 应该是唯一 -->  
  <div>我是div1</div>  
  <div class="box">我是div2</div>  
  <div id="home">我是div3</div>  
  
  <p class="box">我是p元素</p>  
  
  <h2 id="div">我是h2标题</h2>  
  
  <!-- class/id的名称比较复杂 -->  
  <div class="box one"></div>  
  <div class="box-one box-first"></div>  
  <div class="box_one box_first"></div>  
  <!-- 大驼峰/小驼峰 -->  
  <!-- <div class="boxOne BoxFirst"></div> -->  
</body>  
</html>
```

### id 注意事项

一个HTML文档里面的id值是唯一的，不能重复。id值如果由多个单词组成，单词之间可以用中划线-、下划线_连接，也可以使用驼峰标识，最好不要用标签名作为id值

## 属性选择器

- 拥有某一个属性 `[att]`
- 属性等于某个值 `[att=val]`
- 其他了解的(不用记)
	- `[attr*=val]`: 属性值包含某一个值val
	- `[attr^=val]`: 属性值以val开头
	- `[attr$=val]`: 属性值以val结尾
	- `[attr|=val]`: 属性值等于val或者以val开头后面紧跟连接符-
	- `[attr~=val]`: 属性值包含val, 如果有其他值必须以空格和val分割

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    [title] {  
      color: red;  
    }  
  
    [title=div] {  
      background-color: blue;  
    }  
  </style>  
</head>  
<body>  
  <div>我是div元素</div>  
  <div title="div">我也是div元素</div>  
  <p>我是p元素</p>  
  <h2 title="h2">我是h2元素</h2>  
  
</body>  
</html>
```

## 后代选择器

所有的后代(直接/间接的后代)

- 选择器之间以空格分割

直接子代选择器(必须是直接自带)

- 选择器之间以 > 分割;

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* 后代选择器 */    
    .home span {  
      color: red;  
      font-size: 30px;  
    }  
  
    /* .home的子代的span元素设置一个背景 */    
    .home > span {  
      background-color: green;  
    }  
  </style>  
</head>  
<body>  
  <div class="home">  
    <span>啦啦啦啦</span>    
    <div class="box">  
      <p>我是p元素</p>  
      <span class="home-item">呵呵呵呵</span>  
    </div>  
  
    <div class="content">  
      <div class="desc">  
        <p>  
          <span class="home-item">哈哈哈哈</span>  
        </p>  
      </div>  
    </div>  
  </div>  
  
  <!-- 不希望被选中 -->  
  <span>嘻嘻嘻</span>  
  <div>  
    <span>嘿嘿嘿</span>  
  </div>  
  
</body>  
</html>
```

## 兄弟选择器

相邻兄弟选择器

- 使用符号 + 连接

普遍兄弟选择器 

- 使用符号 ~ 连接

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box + .content {  
      color: red;  
    }  
  
    .box ~ div {  
      font-size: 30px;  
    }  
  </style>  
</head>  
<body>  
  <div class="home">  
    <div>叽叽叽叽</div>  
    <div class="box">呵呵呵呵</div>  
    <div class="content">哈哈哈哈</div>  
    <div>嘻嘻嘻嘻</div>  
    <div>嘿嘿嘿嘿</div>  
    <p>我是p元素</p>  
  </div>  
  
</body>  
</html>
```

## 选择器组

### 交集选择器

 需要同时符合两个选择器条件(两个选择器紧密连接)

- 在开发中通常为了精准的选择某一个元素

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    div.box {  
      color: red;  
      font-size: 30px;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  <p class="box">我是p元素</p>  
  
</body>  
</html>
```

### 并集选择器

符合一个选择器条件即可(两个选择器以,号分割)

- 在开发中通常为了给多个元素设置相同的样式

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    body, p, h1, h2 {  
      color: red;  
      font-size: 40px;  
    }  
  </style>  
</head>  
<body>  
  
  <p>我是p元素</p>  
  <h1>我是h1元素</h1>  
  
</body>  
</html>
```

## 伪类

### 了解伪类

什么是伪类呢?

- Pseudo-classes: 翻译过来是伪类
- 伪类是选择器的一种，它用于选择处于特定状态的元素
- 比如我们经常会实现的: 当鼠标放在一个元素上时, 显示另外一个颜色

### 类型

常见的伪类有

1. 动态伪类（dynamic pseudo-classes）
	- :link
	- :visited
	- :hover
	- :active
	- :focus
2. 目标伪类（target pseudo-classes）
	- :target
3. 语言伪类（language pseudo-classes）
	- :lang( )
4. 元素状态伪类（UI element states pseudo-classes）
	- :enabled
	- :disabled
	- :checked
5.  结构伪类（structural pseudo-classes）
	- :nth-child( )
	- :nth-last-child( )
	- :nth-of-type( )
	- :nth-last-of-type( )
	- :first-child
	- :last-child
	- :first-of-type
	- :last-of-type
	- :root
	- :only-child
	- :only-of-type
	- :empty
6. 否定伪类（negation pseudo-classes）
	- :not()

[伪类文档](https://developer.mozilla.org/zh-CN/docs/Web/CSS/Pseudo-classes)

###  动态伪类

使用举例

- a:link 未访问的链接
- a:visited 已访问的链接
- a:hover 鼠标挪动到链接上(重要)
- a:active 激活的链接（鼠标在链接上长按住未松开）

使用注意

- :hover必须放在:link和:visited后面才能完全生效
- :active必须放在:hover后面才能完全生效
- 所以建议的编写顺序是 :link、:visited、:hover、:active
- 除了a元素，:hover、:active也能用在其他元素上

:focus指当前拥有输入焦点的元素（能接收键盘输入）

- 文本输入框一聚焦后，背景就会变红色
	- 因为链接a元素可以被键盘的Tab键选中聚焦，所以:focus也适用于a元素

- 动态伪类编写顺序建议为
	- :link、:visited、:focus、:hover、:active

- 直接给a元素设置样式，相当于给a元素的所有动态伪类都设置了
	- 相当于a:link、a:visited、a:hover、a:active、a:focus的color都是red


```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* a元素的链接从来没有被访问过 */    a:link {  
      color: red;  
    }  
  
    /* a元素被访问过了颜色 */    a:visited {  
      color: green;  
    }  
  
    /* a/input元素聚焦(获取焦点) */  
    a:focus {  
      color: yellow;  
    }  
  
    /* a元素鼠标放到上面 */    a:hover {  
      color: blue;  
    }  
  
    /* 点下去了, 但是还没有松手 */    a:active {  
      color: purple;  
    }  
  
    /* 所有的状态下同样的样式 */    a {  
      color: orange;  
    }  
  </style>  
</head>  
<body>  
  <a href="http://www.mi.com">小米</a>  
  <a href="http://www.baidu.com">百度一下</a>  
  
  <input type="text">  
  
  <div>我是div元素</div>  
  
</body>  
</html>
```

### 结构伪类

#### :nth-child

◼ :nth-child(1)
 是父元素中的第1个子元素
◼ :nth-child(2n)
 n代表任意正整数和0
 是父元素中的第偶数个子元素（第2、4、6、8......个）
 跟:nth-child(even)同义
◼ :nth-child(2n + 1)
 n代表任意正整数和0
 是父元素中的第奇数个子元素（第1、3、5、7......个）
 跟:nth-child(odd)同义
◼ nth-child(-n + 2)
 代表前2个子元素

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    ul li:nth-child(3) {
      color: red;
    }

    /* 0, 1, 2, 3, 4, 5...... */
    ul li:nth-child(2n) {
      color: green;
    }

    ul li:nth-child(2n + 1) {
      color: blue;
    }


    div > div:nth-child(4n + 1) {
      color: orange;
    }

    div > div:nth-child(4n + 2) {
      color: purple;
    }

    div > div:nth-child(4n + 3) {
      color: red;
    }

    div > div:nth-child(4n) {
      color: blue;
    }

    /* 前几个 */
    div > div:nth-child(-n + 5) {
      font-size: 20px;
    }

  </style>
</head>
<body>
  
  <ul>
    <li>列表元素1</li>
    <li>列表元素2</li>
    <li>列表元素3</li>
    <li>列表元素4</li>
    <li>列表元素5</li>
    <li>列表元素6</li>
  </ul>

  <div>
    <div>列表元素1</div>
    <div>列表元素2</div>
    <div>列表元素3</div>
    <div>列表元素4</div>
    <div>列表元素5</div>
    <div>列表元素6</div>
    <div>列表元素7</div>
    <div>列表元素8</div>
    <div>列表元素9</div>
    <div>列表元素10</div>
  </div>

</body>
</html>
```

#### :nth-last-child( )

◼ :nth-last-child()的语法跟:nth-child()类似，不同点是:nth-last-child()从最后一个子元素开始往前计数
 :nth-last-child(1)，代表倒数第一个子元素
 :nth-last-child(-n + 2)，代表最后2个子元素
◼ :nth-of-type()用法跟:nth-child()类似
 不同点是:nth-of-type()计数时只计算同种类型的元素
◼ :nth-last-of-type()用法跟:nth-of-type()类似
 不同点是:nth-last-of-type()从最后一个这种类型的子元素开始往前计数

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 倒数的某一个时 */
    ul > li:nth-last-child(2) {
      color: red;
    }

    /* 倒数的后几个时 */
    ul > li:nth-last-child(-n + 3) {
      font-size: 20px;
    }
  </style>
</head>
<body>
  
  <ul>
    <li>列表元素1</li>
    <li>列表元素2</li>
    <li>列表元素3</li>
    <li>列表元素4</li>
    <li>列表元素5</li>
    <li>列表元素6</li>
    <li>列表元素7</li>
    <li>列表元素8</li>
  </ul>

</body>
</html>
```

#### :nth-of-type( )、:nth-last-of-type( )

其他常见的伪类(了解)

- :first-child ，等同于 :nth-child(1)
- :last-child ，等同于 :nth-last-child(1)
- :first-of-type ，等同于 :nth-of-type(1)
- :last-of-type ，等同于 :nth-last-of-type(1)
- :only-child ，是父元素中唯一的子元素
- :only-of-type ，是父元素中唯一的这种类型的子元素

下面的伪类偶尔会使用

- :root，根元素，就是HTML元素
- :empty代表里面完全空白的元素

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 需求: 选择box中的div元素, 并且是第三个子元素 */
    .box > div:nth-child(3) {
      color: red;
    }

    /* 需求: 选择box中的第三个div元素(排除所有的干扰项) */
    /* 元素:nth-of-type, 只计算符合我元素类型的数量的元素 */
    .box > div:nth-of-type(3) {
      color: blue;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div>我是列表1</div>
    <p>我是p元素</p>
    <span>我是span1</span>
    <span>我是span2</span>
    <span>我是span3</span>
    <span>我是span4</span>
    <div>我是列表2</div>
    <div>我是列表3</div>
    <div>我是列表4</div>
    <div>我是列表5</div>
    <div>我是列表6</div>
    <div>我是列表7</div>
    <div>我是列表8</div>
    <div>我是列表9</div>
    <div>我是列表10</div>
  </div>

</body>
</html>
```

其他常见伪类演示代码

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box > :first-child {
      color: red;
    }

    .box > :only-child {
      font-size: 20px;
      font-weight: 700;
    }

    .box > :only-of-type {
      color: purple;
    }

    /* html元素 */
    :root {
      font-size: 30px;
    }

    :empty {
      width: 100px;
      height: 100px;
      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <span>我是span元素</span>
    <div>列表内容1</div>
    <div>列表内容2</div>
    <div>列表内容3</div>
    <div>列表内容4</div>
    <div>列表内容5</div>
  </div>


  <div class="box">
    <div>我是box的div</div>
    <span>我是span元素</span>
  </div>

  <div class="box">
    <div>我是box的div</div>
    <div>我是box的div</div>
  </div>

  <div class="container"></div>

</body>
</html>
```

### 否定伪类

:not() 的格式是 :not(x)

- x 是一个简单选择器，元素选择器、通用选择器、属性选择器、类选择器、id选择器、伪类（除否定伪类）

:not(x)表示除 x 以外的元素

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
    <meta charset="UTF-8">  
    <meta http-equiv="X-UA-Compatible" content="IE=edge">  
    <meta name="viewport" content="width=device-width, initial-scale=1.0">  
    <title>Document</title>  
    <style>  
        /* .item {  
          color: red;        } */  
        .box :not(.han) {  
            color: blue;  
        }  
    </style>  
</head>  
<body>  
  
<div class="box">  
    <div class="item">列表内容1</div>  
    <div class="item">列表内容2</div>  
    <div class="han">列表内容3</div>  
    <div class="item">列表内容4</div>  
    <div class="item">列表内容5</div>  
    <div>列表内容5</div>  
    <div>列表内容5</div>  
    <div>列表内容5</div>  
</div>  
  
</body>  
</html>
```

## 伪元素

### 介绍

常用的伪元素有

- :first-line、::first-line
- :first-letter、::first-letter
- :before、::before
- :after、::after

为了区分伪元素和伪类，建议伪元素使用2个冒号，比如::first-line

### ::first-line ::first-letter

::first-line可以针对**首行文本设置属性**
::first-letter可以针对**首字母设置属性**

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 800px;
      background-color: #f00;
      color: #fff;
    }

    /* .keyword {
      font-size: 30px;
      color: orange;
    } */

    .box::first-line {
      font-size: 30px;
      color: orange;
    }

    .box::first-letter {
      font-size: 50px;
      color: blue;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <span class="keyword">雁门关，别名西陉关 ，坐落于我国山西省忻</span>州市代县以北约成员国20千米的雁门山。它是长城上的一个关键大关，与宁武关、偏关并称之为“外三关”。坐落于偏关县大河上，辖四侧墙，总长度数百公里。迄今仍有30千米储存完好无损，所有用砖遮盖，沿堤岸耸立，十分壮阔。“边关丁宁岩，山连紫塞，地控大河北，鑫城携手共进强。”这也是前人对偏关的赞扬。早在春秋战国时代，这儿便是赵武灵王攻克胡林的竞技场。唐朝名将在关东建有九龙庙，宋代建有魏镇、杨三关。现有的关城始建明洪武二十三年，是重点学科文物古迹。
  </div>

</body>
</html>
```

### ::before ::after

::before和::after用来在一个元素的内容之前或之后插入其他内容（可以是文字、图片)

- 常通过 content 属性来为一个元素添加修饰性的内容

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .before {
      color: red;
    }

    .after {
      color: blue;
    }

    /* 伪元素 */
    .item::before {
      content: "321";
      color: orange;
      font-size: 20px;
    }

    .item::after {
      /* content: "cba"; */
      content: url("../images/hot_icon.svg");
      color: green;
      font-size: 20px;

      /* 位置不是很好看(以后) */
      position: relative; /* 相对定位 */
      left: 5px;
      top: 2px;
    }

    /* .new::after {
      content: url("../images/new_icon.svg");
    } */

    /* 额外的补充 */
    /* ::after是一个行内级元素 */
    .box5::after {
      /* 使用伪元素的过程中, 不要将content省略 */
      content: "";

      display: inline-block;
      width: 8px;
      height: 8px;
      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <span class="before">123</span>
    我是div元素
    <span class="after">abc</span>
  </div>

  <div class="box2">
    <span class="before">123</span>
    我是box2
    <span class="after">abc</span>
  </div>

  <!-- 伪元素方案 -->
  <div class="box3 item">我是box3</div>
  <div class="box4 item">我是box4</div>

  <!-- 伪元素的补充 -->
  <div class="box5">我是box5</div>

</body>
</html>
```

# CSS继承-层叠-元素类型

## CSS属性的继承

CSS的某些属性具有继承性(Inherited)

- 如果一个属性具备继承性, 那么在该元素上设置后, 它的后代元素都可以继承这个属性;
- 当然, 如果后代元素自己有设置该属性, 那么优先使用后代元素自己的属性(不管继承过来的属性权重多高)

如何知道一个属性是否具有继承性呢?

- 常见的font-size/font-family/font-weight/line-height/color/text-align都具有继承性
- 这些不用刻意去记, 用的多自然就记住了

另外要多学会查阅文档, 文档中每个属性都有标明其继承性的

注意(了解)
- 继承过来的是计算值, 而不是设置值

### 默认继承

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* h1, p, span, strong {  
      color: red;    } */    div.box {  
      color: red;  
    }  
  
  </style>  
</head>  
<body>  
  <div class="box">  
    <h1>我是h1元素</h1>  
    <p>  
      我是p元素  
      <span>哈哈哈</span>  
      <strong>呵呵呵</strong>  
    </p>  
    <span>我是span元素</span>  
  </div>  
  
</body>  
</html>
```

### 继承值计算

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      color: red;  
      /* font-size: 30px; */  
      /* 相对于自身字体(父元素的字体) */  
      /* 浏览器 16px */      font-size: 2em;/* 32px */  
    }  
  
    p {  
      /* font-size: 2em; */  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    box本身的内容  
    <p>我是p元素</p>  
  </div>  
  
</body>  
</html>
```

### 强制继承

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      color: red;  
  
      border: 2px solid purple;  
    }  
  
    .box p {  
      /* 很少用 */      border: inherit;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    <p>我是p元素</p>  
    <h1>我是h1元素</h1>  
  </div>  
  
</body>  
</html>
```

## CSS属性的层叠

CSS的翻译是层叠样式表, 什么是层叠呢?

- 对于一个元素来说, 相同一个属性我们可以通过不同的选择器给它进行多次设置
- 那么属性会被一层层覆盖上去
- 但是最终只有一个会生效

那么多个样式属性覆盖上去, 哪一个会生效呢?

- 选择器的权重, 权重大的生效, 根据权重可以判断出优先级
- 先后顺序, 权重相同时, 后面设置的生效

那么如何知道元素的权重呢?

### 基本演示

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    div {  
      color: red;  
    }  
  
    .box {  
      color: blue;  
    }  
  
    .one {  
      color: green;  
    }  
  
    .first {  
      color: purple;  
    }  
  
    .content {  
      color: orange;  
    }  
  </style>  
</head>  
<body>  
  
  <div class="box one first content">我是box</div>  
  
</body>  
</html>
```

### 选择器权重

按照经验，为了方便比较CSS属性的优先级，可以给CSS属性所处的环境定义一个权值（权重）

- !important：10000
- 内联样式：1000
- id选择器：100
- 类选择器、属性选择器、伪类：10
- 元素选择器、伪元素：1
- 通配符：0

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    div.box {  
      color: red !important; /* 10000 */  
    }  
  
    /* id选择器: 100 */  
    #main {  
      color: orange;  
    }  
  
    /* 类选择器: 10 */  
    .box {  
      color: blue;  
    }  
  
    /* 元素选择器: 1 */  
    div {  
      color: purple;  
    }  
  
    /* 通配选择器: 0 */  
    * {  
      color: yellow;  
    }  
  </style>  
</head>  
<body>  
  <!-- 内联样式: 1000 -->  
  <div id="main" class="box one two" style="color: blue;">我是div元素</div>  
  
</body>  
</html>
```

## CSS属性的类型

在前面我们会经常提到div是块级元素会独占一行, span是行内级元素会在同一行显示

- 到底什么是块级元素, 什么是行内级元素呢?

HTML定义元素类型的思路

- HTML元素有很多, 比如h元素/p元素/div元素/span元素/img元素/a元素等等
- 当我们把这个元素放到页面上时, 这个元素到底占据页面中一行多大的空间呢
	- 为什么我们这里只说一行呢? 因为垂直方向的高度通常是内容决定的
- 比如一个h1元素的标题, 我们必然是希望它独占一行的, 其他的内容不应该和我的标题放在一起
- 比如一个p元素的段落, 必然也应该独占一行, 其他的内容不应该和我的段落放在一起
- 而类似于img/span/a元素, 通常是对内容的某一个细节的特殊描述, 没有必要独占一行

所以, 为了区分哪些元素需要独占一行, 哪些元素不需要独占一行, HTML将元素区分(本质是通过CSS的)成了两类:

- 块级元素（block-level elements）: 独占父元素的一行
- 行内级元素（inline-level elements）:多个行内级元素可以在父元素的同一行中显示

事实上元素没有本质的区别:

- div是块级元素, span是行内级元素
- div之所以是块级元素仅仅是因为浏览器默认设置了display属性而已;
- 我们可以通过display来改变元素的特性

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 10 */
    .box {
      height: 100px;
      background-color: #f00;
      color: #fff;

      /* 修改div元素的特性: 层叠 */
      display: inline;
    }

    span {
      background-color: #0f0;
      display: block;
    }
  </style>
</head>
<body>
  
  <div class="box">我是div元素</div>
  <span>我是span元素</span>
  <a href="#">百度一下</a>

</body>
</html>
```
## display属性

CSS中有个display属性，能修改元素的显示类型，有5个常用值

- block：让元素显示为块级元素
- inline：让元素显示为行内级元素
- inline-block：让元素同时具备行内级、块级元素的特征
- none：隐藏元素
- flex：flex布局

### 特性

block 元素

- 独占父元素的一行
- 可以随意设置宽高
- 高度默认由内容决定

inline-block 元素

- 跟其他行内级元素在同一行显示
- 可以随意设置宽高
- 可以这样理解
	- 对外来说，它是一个行内级元素
	- 对内来说，它是一个块级元素

inline 元素
 
- 跟其他行内级元素在同一行显示
- 不可以随意设置宽高
- 宽高都由内容决定

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* 宽高不满意: 自己来设置 */    div {  
      background-color: #f00;  
  
      width: 200px;  
      height: 200px;  
    }  
  
    span {  
      background-color: #0f0;  
  
      width: 200px;  
      height: 200px;  
    }  
  
    img {  
      height: 200px;  
      height: 150px;  
    }  
  
    input {  
      height: 60px;  
    }  
  </style>  
</head>  
<body>  
  <div>我是div元素</div>  
  
  <!-- 行内级元素设置宽度和高度不生效??? 行内非替换元素不可以设置宽高 -->  
  <span>我是span元素</span>  
  
  <!-- 补充:  -->  
  <!-- img元素: inline - replaced -> 行内替换元素 -->  
  <!-- 行内替换元素:   
1> 和其他的行内级元素在同一行显示  
    2> 可以设置宽度和高度   
-->  
  <img src="../images/gouwujie01.jpg" alt="">  
  <input type="text">  
  
</body>  
</html>
```

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      background-color: #f00;  
  
      /* display: inline; */  
      /*inline: 你可以和其他的元素在同一行显示  
        block: 可以设置宽度和高度  
      */      display: inline-block;  
  
      width: 200px;  
      height: 100px;  
    }  
  </style>  
</head>  
<body>  
  <a href="#">百度一下</a>  
  <div class="box">我是box</div>  
  <span>我是span元素</span>  
  
</body>  
</html>
```

### 注意事项

块级元素、inline-block元素

- 一般情况下，可以包含其他任何元素（比如块级元素、行内级元素、inline-block元素）
- 特殊情况，p元素不能包含其他块级元素

行内级元素（比如a、span、strong等）

- 一般情况下，只能包含行内级元素

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

  <!-- h1/p/div -->
  <!-- span/a/img/strong -->

  <div>
    <h1></h1>
    <p></p>
    <a href=""></a>
    <img src="" alt="">
  </div>

  <!-- 特殊: 不要在p元素中放div元素 -->
  <p>
    123
    <div>我是div元素</div>
    abc
  </p>

  <!-- 行内级元素中不要放块级元素 -->
  <span>
    321
    <div></div>
    <p></p>
    cba
  </span>

</body>
</html>
```

## 元素的隐藏

方法一: display设置为none

- 元素不显示出来, 并且也不占据位置, 不占据任何空间(和不存在一样)

方法二: visibility设置为hidden

- 设置为hidden, 虽然元素不可见, 但是会占据元素应该占据的空间
- 默认为visible, 元素是可见的;

方法三: rgba设置颜色, 将a的值设置为0

- rgba的a设置的是alpha值, 可以设置透明度, 不影响子元素

方法四: opacity设置透明度, 设置为0

- 设置整个元素的透明度, 会影响所有的子元素

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      display: none;  
    }  
  
    .content {  
      visibility: hidden;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">我是div元素</div>  
  <div>哈哈哈哈</div>  
  
  <div class="content">我是content</div>  
  <div>呵呵呵呵</div>  
  
</body>  
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* alpha: 只是设置当前color/bgc其中的颜色透明度为某一个值, 不会影响子元素 */
    .box1 {
      /* 不是很推荐 */
      /* color module */
      /* color: #ff000088; */
      /* webpack -> postcss -> browserslist -> rgba() */
      /* 推荐下面的写法 a -> alpha 0~1 */
      /* color: rgba(255, 0, 0, 0.5); */

      /* 通过颜色来隐藏 */
      /* color: rgba(0, 0, 0, 0) */

      /* 通过背景颜色透明度来隐藏 */
      /* background-color: rgba(0, 0, 0, 0); */
      background-color: transparent; /* rgba(0,0,0,0) */
    }

    /* opacity: 设置透明度, 并且会携带所有的子元素都有一定的透明度 */
    .box2 {
      opacity: 0.5;
    }
  </style>
</head>
<body>
  
  <div class="box1">
    我是box1
    <img src="../images/gouwujie01.jpg" alt="">
  </div>
  <div class="box2">
    我是box2
    <img src="../images/gouwujie01.jpg" alt="">
  </div>

</body>
</html>
```

## overflow属性

overflow用于控制内容溢出时的行为

- visible：溢出的内容照样可见
- hidden：溢出的内容直接裁剪
- scroll：溢出的内容被裁剪，但可以通过滚动机制查看
	- 会一直显示滚动条区域，滚动条区域占用的空间属于width、height
- auto：自动根据内容是否溢出来决定是否提供滚动机制

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      width: 300px;  
      height: 100px;  
      background-color: #f00;  
  
      /* overflow: visible */  
      overflow: auto;  
    }  
  </style>  
</head>  
<body>  
  <div class="box">  
    从充满历史气息的传统对称式花园，到各地功能与美感俱佳的小小菜园，再到与大艺术家们设计园林的邂逅，还是蒙顿·唐，说着一口流利的法语，寻访法国的每个角落，让人领略到原汁原味的法国风情，体会法国人融入骨子里的浪漫与优雅。  
  </div>  
  
</body>  
</html>
```

## 样式不生效排查技巧

为何有时候编写的CSS属性不好使，有可能是因为

- 选择器的优先级太低
- 选择器没选中对应的元素
- CSS属性的使用形式不对
	- 元素不支持此CSS属性，比如span默认是不支持width和height的
	- 浏览器不支持此CSS属性，比如旧版本的浏览器不支持一些css module3的某些属性
	- 被同类型的CSS属性覆盖，比如font覆盖font-size

建议

- 充分利用浏览器的开发者工具进行调试（增加、修改样式）、查错

# 盒子模型

## 认识盒子模型

事实上, 我们可以把HTML每一个元素看出一个个的盒子

HTML中的每一个元素都可以看做是一个盒子，如右下图所示，可以具备这4个属性

内容（content）

- 元素的内容width/height

内边距（padding）

- 元素和内容之间的间距

边框（border）

- 元素自己的边框

外边距（margin）

- 元素和其他元素之间的间距

![](image/Pasted%20image%2020250520170346.png)

因为盒子有四边, 所以margin/padding/border都包括top/right/bottom/left四个边

![](image/Pasted%20image%2020250520170431.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      width: 100px;  
      height: 100px;  
      background-color: #f00;  
  
      /* padding: 0;  
      border: 0 solid #f00;      margin: 0; */    }  
  </style>  
</head>  
<body>  
  <div class="box">我是box</div>  
  
</body>  
</html>
```

## 内容width/height

设置内容是通过宽度和高度设置的

- 宽度设置: width
- 高度设置: height

注意: 对于行内级非替换元素来说, 设置宽高是无效的

另外我们还可以设置如下属性

- min-width：最小宽度，无论内容多少，宽度都大于或等于min-width
- max-width：最大宽度，无论内容多少，宽度都小于或等于max-width
- 移动端适配时, 可以设置最大宽度和最小宽度;

下面两个属性不常用

- min-height：最小高度，无论内容多少，高度都大于或等于min-height
- max-height：最大高度，无论内容多少，高度都小于或等于max-height

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      /* content */  
      width: 200px;  
      height: 200px;  
      background-color: #0f0;  
    }  
  </style>  
</head>  
<body>  
  <div class="box"></div>  
  
</body>  
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      background-color: #f00;

      /* width */
      /* auto 交给浏览器来决定 */
      /* 块级元素: 独占一行(父元素) */
      width: auto;
    }

    .title {
      /* 行内级: 包裹内容 */
      display: inline-block;
      width: auto;
    }

    img {
      width: auto;
      width: 200px;
    }
  </style>
</head>
<body>
  
  <div class="box">我是box</div>
  <span class="title">我是span元素</span>
  <img src="../images/gouwujie01.jpg" alt="">

</body>
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>

    body {
      /* inline-level boxs */
      /* text-align: center; */
    }
    .home {
      height: 2000px;
      background-color: #f00;

      /* 最大的宽度: 750px */
      max-width: 750px;

      /* 最小的宽度: 500px */
      min-width: 600px;

      /* 块级水平元素居中 */
      margin: 0 auto;
    }
  </style>
</head>
<body>
  
  <div class="home"></div>

</body>
</html>
```

## 内边距padding

padding属性用于设置盒子的内边距, 通常用于设置边框和内容之间的间距

padding包括四个方向, 所以有如下的取值

- padding-top：上内边距
- padding-right：右内边距
- padding-bottom：下内边距
- padding-left：左内边距

padding单独编写是一个缩写属性

- padding-top、padding-right、padding-bottom、padding-left的简写属性
- padding缩写属性是从零点钟方向开始, 沿着顺时针转动的, 也就是上右下左;

### 其他值

padding并非必须是四个值, 也可以有其他值

![](image/Pasted%20image%2020250520170731.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      /* 设置一个红色的实体边框 */
      border: 1px solid red;
      display: inline-block;

      /* line-height */
      /* line-height: 36px; */

      /* 内边距: padding */
      /* 
      padding-top: 10px;
      padding-right: 20px;
      padding-bottom: 30px;
      padding-left: 40px; 
      */

      /* 等价于: 缩写属性 */
      padding: 10px 20px 30px 40px;

      /* 其他值的情况 */
      /* 3个值 */
      /* 省略left -> 使用right */
      padding: 10px 20px 30px;
      /* 2个值 */
      /* 省略: left -> 使用right */
      /* 省略: bottom -> 使用top */
      padding: 10px 20px;
      /* 1个值 */
      /* 上下左右都使用同一个值 */
      padding: 10px;
    }
  </style>
</head>
<body>
  
  <div class="box">我是box</div>

</body>
</html>
```

## 边框/圆角border

border用于设置盒子的边框

边框相对于content/padding/margin来说特殊一些

- 边框具备宽度 width
- 边框具备样式 style
- 边框具备颜色 color

### 设置边框的方式

边框宽度

- border-top-width、border-right-width、border-bottom-width、border-left-width
- border-width是上面 4 个属性的简写属性

边框颜色

- border-top-color、border-right-color、border-bottom-color、border-left-color
- border-color是上面 4 个属性的简写属性

边框样式

- border-top-style、border-right-style、border-bottom-style、border-left-style
- border-style是上面 4 个属性的简写属性

### 边框的样式设置值

边框的样式有很多, 我们可以了解如下的几个:

- groove：凹槽, 沟槽, 边框看上去好象是雕刻在画布之内
- ridge：山脊, 和 grove 相反，边框看上去好象是从画布中凸出来

![](image/Pasted%20image%2020250520220552.png)

### 同时设置边框样式的方式


如果我们相对某一边同时设置 宽度 样式 颜色, 可以进行如下设置
- border-top
- border-right
- border-bottom
- border-left
- border：统一设置4个方向的边框

边框颜色、宽度、样式的编写顺序任意

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      display: inline-block;

      width: 300px;
      height: 300px;

      /* width */
      /* 
      border-top-width: 10px;
      border-right-width: 20px;
      border-bottom-width: 30px;
      border-left-width: 40px; 
      */
      /* 
      border-width: 10px 20px 30px 40px; 
      */

      /* style */
      /* 
      border-top-style: solid;
      border-right-style: dashed;
      border-bottom-style: groove;
      border-left-style: ridge; 
      */
      /* 
      border-style: solid dashed groove ridge; 
      */

      /* color */
      /* border-top-color: red;
      border-right-color: blue;
      border-bottom-color: green;
      border-left-color: orange; 
      */
      /* 
      border-color: red blue green orange; 
      */

      /* 总缩写属性 */
      border: 10px solid red;
    }
  </style>
</head>
<body>
  
  <div class="box">我是box</div>

</body>
</html>
```

### 圆角

border-radius 用于设置盒子的圆角

border-radius常见的值

- 数值: 通常用来设置小的圆角, 比如6px
- 百分比: 通常用来设置一定的弧度或者圆形

border-radius事实上是一个缩写属性

- 将这四个属性
	- border-top-left-radius
	- border-top-right-radius
	- border-bottom-right-radius
	- border-bottom-left-radius
	- 简写为一个属性，开发中比较少见一个个圆角设置

如果一个元素是正方形, 设置border-radius大于或等于50%时，就会变成一个圆

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>

    div {
      width: 180px;
      height: 100px;
      background-color: #f00;

      border: 10px solid green;
    }

    .box {
      /* 设置圆角 */
      /* 设置具体的数值 */
      /* border-radius: 20px; */
      /* 设置百分比 */
      /* 百分比相对于谁, 了解即可 */
      border-radius: 10%;
    }

    .content {
      border-radius: 20px;
    }

    .home {
      width: 100px;
      height: 100px;
      border: 10px solid red;
      background-color: #0f0;

      border-radius: 50%;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>
  <div class="content"></div>


  <div class="home"></div>

</body>
</html>
```

## 外边距margin

margin属性用于设置盒子的外边距, 通常用于元素和元素之间的间距

margin包括四个方向, 所以有如下的取值

- margin-top：上内边距
- margin-right：右内边距
- margin-bottom：下内边距
- margin-left：左内边距

### 其他值

margin单独编写是一个缩写属性

- margin-top、margin-right、margin-bottom、margin-left的简写属性
- margin缩写属性是从零点钟方向开始, 沿着顺时针转动的, 也就是上右下左

margin也并非必须是四个值, 也可以有其他值;

![](image/Pasted%20image%2020250520223139.png)

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    /* 暂时解决方案 */    body {  
      font-size: 0;  
    }  
  
    .box {  
      display: inline-block;  
      width: 100px;  
      height: 100px;  
      background-color: #f00;  
  
      /* margin-bottom: 30px; */  
      /* margin-right: 30px; */    }  
  
    .container {  
      display: inline-block;  
      width: 100px;  
      height: 100px;  
      background-color: #0f0;  
  
      /* margin-top: 30px; */  
      /* margin-left: 30px; */  
      /* 缩写属性 */      margin: 0 20px;  
    }  
  </style>  
</head>  
<body>  
  <div class="box"></div>  
  
  <div class="container"></div>  
  
</body>  
</html>
```

- padding 和 margin 对比

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 300px;
      height: 300px;
      background-color: #f00;

      /* padding-left: 30px;
      box-sizing: border-box; */
      /* overflow: auto; */
      padding-top: 100px;
      box-sizing: border-box;
    }

    .container {
      width: 100px;
      height: 100px;
      background-color: #0f0;

      margin-left: 100px;
      /* margin-top: 100px; */
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div class="container"></div>
  </div>

</body>
</html>
```

### 上下margin的传递

margin-top 传递

- 如果块级元素的顶部线和父元素的顶部线重叠，那么这个块级元素的 margin-top 值会传递给父元素

margin-bottom 传递

- 如果块级元素的底部线和父元素的底部线重写，并且父元素的高度是 auto，那么这个块级元素的 margin-bottom 值会传递给父元素

如何防止出现传递问题？

- 给父元素设置 padding-top \ padding-bottom
- 给父元素设置 border
- 触发BFC: 设置 overflow 为 auto

建议

- margin 一般是用来设置兄弟元素之间的间距
- padding 一般是用来设置父子元素之间的间距

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  
  <style>
    .box {
      width: 300px;
      /* height: auto; */
      background-color: #f00;
    }

    .container {
      width: 100px;
      height: 100px;
      background-color: #0f0;

      margin-bottom: 100px;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div class="container"></div>
  </div>

  <div>哈哈哈哈哈啊</div>

</body>
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 300px;
      height: 300px;
      background-color: #f00;

      /* border: 1px solid rgba(0,0,0,0); */
      overflow: auto;
    }

    .container {
      width: 100px;
      height: 100px;
      background-color: #0f0;

      /* 左右是不会传递 */
      /* margin-left: 30px; */

      margin-top: 100px;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div class="container"></div>
  </div>

</body>
</html>
```

### 上下margin的折叠

垂直方向上相邻的2个margin（margin-top、margin-bottom）有可能会合并为1个margin，这种现象叫做collapse（折叠）

水平方向上的margin（margin-left、margin-right）永远不会collapse

折叠后最终值的计算规则

- 两个值进行比较，取较大的值

如何防止margin collapse

- 只设置其中一个元素的margin

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box1 {
      height: 100px;
      background-color: #f00;

      margin-bottom: 30px;
    }

    .box2 {
      height: 100px;
      background-color: #0f0;

      margin-top: 50px;
    }
  </style>
</head>
<body>
  
  <div class="box1"></div>
  <div class="box2"></div>

</body>
</html>
```

#### 对应的情况

两个兄弟块级元素之间上下margin的折叠

父子块级元素之间margin的折叠

![](image/Pasted%20image%2020250520224002.png)

## 轮廓和文字阴影

### 外轮廓

outline表示元素的外轮廓

- 不占用空间
- 默认显示在border的外面

outline相关属性有

- outline-width: 外轮廓的宽度
- outline-style：取值跟border的样式一样，比如solid、dotted等
- outline-color: 外轮廓的颜色
- outline：outline-width、outline-style、outline-color的简写属性，跟border用法类似

应用实例

- 去除a元素、input元素的focus轮廓效果

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 100px;
      height: 100px;
      background-color: #f00;

      border: 50px solid orange;
      padding: 30px;

      outline: 30px solid #0f0;
    }

    /* 行内级元素设置margin-top无效 */
    a {
      margin-top: 100px;
      display: inline-block;

      outline: none;
    }

    input {
      outline: none;
    }

    /* a:focus {
      outline: none;
    } */
  </style>
</head>
<body>
  
  <div class="box"></div>

  <a href="#">百度一下</a>
  <input type="text">

</body>
</html>
```

### 盒子阴影

box-shadow属性可以设置一个或者多个阴影

- 每个阴影用`<shadow>`表示
- 多个阴影之间用逗号,隔开，从前到后叠加

我们可以通过一个网站测试盒子的阴影

- https://html-css-js.com/css/generator/box-shadow/

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 100px;
      height: 100px;
      background-color: #f00;

      box-shadow: 5px 5px 10px orange, 10px 10px 10px green;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

### 文字阴影

text-shadow用法类似于box-shadow，用于给文字添加阴影效果

我们可以通过一个网站测试文字的阴影:

- https://html-css-js.com/css/generator/box-shadow/

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      font-size: 50px;
      font-weight: 700;

      text-shadow: 5px 5px 5px orange, 10px 10px 5px blue, 15px 15px 5px green;
    }
  </style>
</head>
<body>
  
  <div class="box"> Hello Coderwhy </div>

</body>
</html>
```

## 行内非替换元素的注意事项

以下属性对行内级非替换元素不起作用

- width、height、margin-top、margin-bottom

以下属性对行内级非替换元素的效果比较特殊

- padding-top、padding-bottom、上下方向的border

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .content {  
      background-color: #f00;  
      color: white;  
  
      /* 内容: width/height(压根不生效) */  
      width: 300px;  
      height: 300px;  
  
      /* 内边距: padding */  
      /* 特殊: 上下会被撑起来, 但是不占据空间 */      /* padding: 50px; */  
      /* 边框: border */  
      /* 特殊: 上下会被撑起来, 但是不占据空间 */      /* border: 50px solid orange; */  
      /* 外边距: margin */  
      /* 特殊： 上下的margin是不生效的 */      margin: 50px;  
    }  
  </style>  
</head>  
<body>  
  <span class="content">  
    我是span内容, 哈哈哈  
  </span>  
  aaaaaaa  
  <div>bbbbbb</div>  
  
</body>  
</html>
```

## 背景色和前景色

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 
      1> 背景色有没有设置到border下面(有设置)
      2> 前景色会在border没有设置颜色的情况下, 显示出来color颜色
    */
    .box {
      width: 100px;
      height: 100px;
      background-color: #f00;
      color: orange;
      padding: 30px;
      border: 10px solid;
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```
## box-sizing

box-sizing用来设置盒子模型中宽高的行为

content-box

- padding、border都布置在width、height外边

border-box

- padding、border都布置在width、height里边

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box1 {
      box-sizing: content-box;

      width: 100px;
      height: 100px;
      background-color: #f00;

      padding: 30px;
      border: 10px solid orange;
    }

    .box2 {
      box-sizing: border-box;
      width: 100px;
      height: 100px;
      background-color: #0f0;

      padding: 30px;
      border: 10px solid purple;
    }
  </style>
</head>
<body>  
  

  <div class="box1"></div>
  <div class="box2"></div>

</body>
</html>
```

### content-box

![](image/Pasted%20image%2020250520230603.png)

### border-box

![](image/Pasted%20image%2020250520230614.png)

## 居中总结

在一些需求中，需要元素在父元素中居中显示（父元素一般都是块级元素、inline-block）

水平居中

  1. 行内级元素: 
	- 设置父元素的text-align: center
  2. 块级元素:
	- 设置当前块级元素(宽度) margin: 0 auto;
  3. 绝对定位
	- 元素有宽度情况下, left0/right0/margin: 0 auto;
  4. flex
	- justify-content: center

垂直居中

1. 绝对定位
	  - 必须使用定位(脱离标准流)
	  - 必须给元素设置高度
2. flex布局
	- 当前flex局部中所有的元素都会被垂直居中
	- 相对来说, 兼容性差一点点(基本可以忽略)
3. top/translate(个人推荐, 不好理解)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      /* position: relative; */
      /* display: flex;
      align-items: center; */

      height: 300px;
      background-color: orange;
    }

    .box1 {
      position: absolute;
      width: 100px;
      /* height: 100px; */
      top: 0;
      bottom: 0;
      margin: auto 0;
      background-color: #f00;
    }

    .box2 {
      background-color: #f00;
    }

    .box3 {
      display: inline-block;
      height: 100px;
      background-color: #f00;

      /* 两件事情:
          1.让元素向下位移父元素的50%
          2.让元素向上位移自身的50% 
      */
      /* margin-top的百分比是相对于包含块(父元素)的宽度 */
      /* margin-top: 50%; */
      position: relative;
      top: 50%;
      transform: translate(0, -50%);
    }
  </style>
</head>
<body>
  
  <!-- 
    水平居中:
      1.行内级元素: 
        * 设置父元素的text-align: center
      2.块级元素:
        * 设置当前块级元素(宽度) margin: 0 auto;
      3.绝对定位
        * 元素有宽度情况下, left0/right0/margin: 0 auto;
      4.flex
        * justify-content: center
   -->

  <!--
    垂直居中:
      1.绝对定位
        * 元素有高度情况下, top0/bottom0/margin: auto 0;
  -->
  <!-- 
    1.垂直居中: 绝对定位
    弊端:
      1> 必须使用定位(脱离标准流)
      2> 必须给元素设置高度
   -->
  <!-- <div class="container">
    <div class="box1">coderwhy</div>
  </div> -->

  <!-- 
    2.垂直居中: flex布局(直接使用flex)
    弊端:
      1> 当前flex局部中所有的元素都会被垂直居中
      2> 相对来说, 兼容性差一点点(基本可以忽略)
   -->
   <!-- <div class="container">
     <div class="box2">flex布局的居中</div>
     aaaa
   </div> -->

   <!-- 
    3.垂直居中: top/translate(个人推荐, 不好理解)
  -->
  <div class="container">
    <div class="box3">top/translate</div>
    aaaaa
  </div>

</body>
</html>
```

# CSS元素定位

## 标准流

默认情况下，元素都是按照 normal flow（标准流、常规流、正常流、文档流【document flow】）进行排布

- 从左到右、从上到下按顺序摆放好
- 默认情况下，互相之间不存在层叠现象

![](image/Pasted%20image%2020250521145003.png)

### 使用 margin padding 调整位置

在标准流中，可以使用margin、padding对元素进行定位

 - 其中margin还可以设置负数（特殊场景重叠使用）

比较明显的缺点是

- 设置一个元素的margin或者padding，通常会影响到标准流中其他元素的定位效果
- 不便于实现元素层叠的效果

如果我们希望一个元素可以跳出标准量,单独的对某个元素进行定位呢?

- 我们可以通过 position 属性来进行设置;

### 认识元素的定位

定位允许您从正常的文档流布局中取出元素，并使它们具有不同的行为:

- 例如放在另一个元素的上面
- 或者始终保持在浏览器视窗内的同一位置

定位在开发中非常常见

![](image/Pasted%20image%2020250521145452.png)

### 认识 position 属性

利用 position 可以对元素进行定位，常用取值有 5 个

![](image/Pasted%20image%2020250521145620.png)

默认值

- static ：默认值, 静态定位

使用下面的值, 可以让元素变成 定位元素(positioned element)

- relative ：相对定位
- absolute ：绝对定位
- fixed ：固定定位
- sticky ：粘性定位

## 静态定位

position属性的默认值

- 元素按照normal flow布局
- left 、right、top、bottom没有任何作用

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .box {  
      display: inline-block;  
      position: static;  
  
      left: 0;  
      top: 100px;  
      bottom: 20px;  
      right: 30px;  
    }  
  </style>  
</head>  
<body>  
  <div>div元素</div>  
  <span>span元素</span>  
  <img src="../images/gouwujie01.jpg" alt="">  
  <div class="box"></div>  
  
</body>  
</html>
```

## 相对定位

元素按照normal flow布局

可以通过left、right、top、bottom进行定位

- 定位参照对象是元素自己原来的位置

left、right、top、bottom用来设置元素的具体位置，对元素的作用如下图所示

![](image/Pasted%20image%2020250521145921.png)

相对定位的应用场景

- 在不影响其他元素位置的前提下，对当前元素位置进行微调

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    .text {  
      /* margin-left: 30px; */    
      /* relative: 相对定位 */      position: relative;  
      left: -30px;  
      top: -50px;  
      /* bottom: 50px;  
      right: 30px; */    }  
  </style>  
</head>  
<body>  
  <span>我是span元素</span>  
  <strong class="text">我是strong元素</strong>  
  <img src="../images/kobe01.jpg" alt="">  
  <div>我是div元素</div>  
  
</body>  
</html>
```

### 小案例

#### 案例一 上角标

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    div {
      font-size: 20px;
    }

    span {
      font-size: 12px;
      position: relative;
      bottom: 8px;
    }
  </style>
</head>
<body>
  
  <div>
    3<span>2</span> + 2<span>3</span> = 17
  </div>

</body>
</html>
```

#### 案例二 让背景图片居中

使用 background

```html
<!DOCTYPE html>  
<html lang="en">  
<head>  
  <meta charset="UTF-8">  
  <meta http-equiv="X-UA-Compatible" content="IE=edge">  
  <meta name="viewport" content="width=device-width, initial-scale=1.0">  
  <title>Document</title>  
  <style>  
    body {  
      margin: 0;  
      padding: 0;  
    }  
  
    .box {  
      height: 489px;  
      background: #f00 url(../images/mhxy.jpg) center;  
    }  
  </style>  
</head>  
<body>  
  <div class="box"></div>  
  
</body>  
</html>
```

使用相对定位实现，比较难想

`margin-left: 50%`

- 这个属性将图片的左外边距设置为父容器宽度的 50%。这会：

	- 把图片的**左边缘**推到父容器的水平中点位置
	- 此时图片本身还保持原位置，只是容器内起始点移动了

`left: -960px`（关键）

- 这里的 960px 是图片宽度的一半（图片宽 1920px）。这个负值会：

	- 将图片**向左移动自身宽度的一半**
	- 由于之前图片左边缘已经在容器中点，现在向左移动一半宽度后，图片中心点就与容器中点对齐了

这种组合实际上是在模拟 `transform: translateX(-50%)` 的效果：

1. 先用 `margin-left: 50%` 定位到中点
2. 再用固定像素值 `left: -960px` 回拉一半宽度

- **固定像素值的局限性**：这种方法需要知道图片确切宽度（1920px），不够灵活
- **更好的现代方案**：建议改用：

```css
    .box img {
      position: relative;
      left: 50%;
      transform: translateX(-50%);
    }
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      margin: 0;
      padding: 0;
    }

    .box {
      height: 489px;
      background-color: #f00;
      overflow: hidden;
    }

    .box img {
      position: relative;
      /* left: 图片的一半 */
      left: -960px;
      /* translate中的百分比是相对于自己 */
      /* transform: translate(-50%); */

      /* 向右边移动div的一半 */
      margin-left: 50%;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <img src="../images/mhxy.jpg" alt="">
  </div>

</body>
</html>
```

## 固定定位

元素脱离 normal flow（脱离标准流、脱标）

可以通过 left、right、top、bottom 进行定位

定位参照对象是视口（ viewport ）

当画布滚动时，固定不动

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .text {
      position: fixed;
      right: 30px;
      bottom: 30px;
    }
  </style>
</head>
<body>
  
  <span>我是span元素</span>
  <strong class="text">我是strong元素</strong>
  <img src="../images/kobe01.jpg" alt="">
  <div>我是div元素</div>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>
  <br><br><br><br>

</body>
</html>
```

### 小案例

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .handle {
      position: fixed;
      right: 30px;
      bottom: 30px;
    }

    .handle .item {
      width: 80px;
      height: 40px;
      text-align: center;
      line-height: 40px;
      background-color: brown;
      color: #fff;
      border-radius: 8px;
      cursor: pointer;
    }

    .handle .item:hover {
      background-color: red;
    }

    .top {
      margin-bottom: 10px;
    }
  </style>
</head>
<body>
  
  <div class="handle">
    <div class="item top">顶部</div>
    <div class="item bottom">反馈</div>
  </div>

  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>
  <br><br><br><br><br>

</body>
</html>
```

## 绝对定位

元素脱离 normal flow（脱离标准流、脱标）

可以通过 left、right、top、bottom 进行定位

- 定位参照对象是最邻近的定位祖先元素
- 如果找不到这样的祖先元素，参照对象是视口

定位元素（ positioned element ）

- position 值不为 static 的元素
- 也就是 position 值为 relative、absolute、fixed 的元素

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 1000px;
      height: 800px;
      background-color: #f00;

      /* position: fixed; */
      position: relative;
      top: 0;
    }

    .box {
      position: relative;

      width: 600px;
      height: 400px;
      background-color: #0f0;
    }

    strong {
      /* 脱离标准版 */
      position: absolute;

      /* 设置的四个值 */
      /* 在没有祖先元素定位的情况下, 相对于的是谁? 视口 */
      right: 0;
      top: 0;
    }

    img {
      width: 100px;
      height: 100px;
    }
  </style>
</head>
<body>
  <div>哈哈哈啊</div>
  <div class="container">
    <div class="box">
      <span>我是span元素</span>
      <strong>我是strong元素</strong>
      <img src="../images/gouwujie01.jpg" alt="">
      <div>我是div元素</div>
    </div>
  </div>
  <div>呵呵呵呵</div>

</body>
</html>
```

### 小案例

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 重置代码 */
    a {
      text-decoration: none;
      color: #333;
    }

    /* 公共的CSS */
    .sprite_01 {
      background-image: url(../images/music_sprite_01.png);
      display: inline-block;
    }

    .sprite_02 {
      background-image: url(../images/music_sprite_02.png);
      display: inline-block;
    }

    .sprite_02_icon_music {
      width: 14px;
      height: 11px;
      background-position: 0 -24px;
    }

    .sprite_02_icon_play {
      width: 16px;
      height: 17px;
      background-position: 0 0;
    }

    /* 布局代码 */
    .item {
      width: 140px;
      margin: 0 auto;
    }

    .item .top {
      position: relative;
    }

    .item .top img {
      /* 将图片下面的多出来的区域去除 */
      vertical-align: top;
      /* display: block; */
    }

    .item .top .cover {
      position: absolute;
      top: 0;
      bottom: 0;
      left: 0;
      right: 0;

      background-image: url(../images/music_sprite_01.png);
      background-position: 0 0;
    }

    .item .top .info {
      position: absolute;
      bottom: 0;
      left: 0;
      right: 0;
      height: 27px;
      padding-left: 10px;
      line-height: 27px;

      font-size: 12px;
      color: #ccc;

      background-image: url(../images/music_sprite_01.png);
      background-position: 0 -537px;
    }

    .item .top .info .icon-music {
      position: relative;
      top: 1px;
      /* display: inline-block; */
      /* width: 14px;
      height: 11px; */

      /* background-image: url(../images/music_sprite_02.png); */
      /* background-position: 0 -24px; */
    }

    .item .top .info .count {
      margin-left: 4px;
    }

    .item .top .info .icon-play {
      position: absolute;
      top: 0;
      bottom: 0;
      right: 10px;
      margin: auto 0;

      /* display: inline-block; */
      /* width: 16px;
      height: 17px; */
      /* background-image: url(../images/music_sprite_02.png); */
      /* background-position: 0 0; */
    }


    /* 底部的样式 */
    .item .bottom {
      display: block;
      margin-top: 8px;
      font-size: 14px;
    }

    .item .bottom:hover {
      text-decoration: underline;
    }
  </style>
</head>
<body>
  
  <div class="item">
    <div class="top">
      <img src="../images/music_album01.jpg" alt="音乐封面">
      <a class="cover" href="#"></a>
      <div class="info">
        <i class="sprite_02 sprite_02_icon_music icon-music"></i>
        <span class="count">62万</span>
        <i class="sprite_02 sprite_02_icon_play icon-play"></i>
      </div>
    </div>
    <a class="bottom" href="#">
      天气好的话，把耳机分给我一半吧
    </a>
    <i class="sprite_02 sprite_02_icon_play"></i>
    <i class="sprite_02 sprite_02_icon_music"></i>
  </div>

</body>
</html>
```

## 粘性定位

另外还有一个定位的值是position: sticky，比起其他定位值要新一些.

- sticky 是一个大家期待已久的属性
- 可以看做是相对定位和固定(绝对)定位的结合体
- 它允许被定位的元素表现得像相对定位一样，直到它滚动到某个阈值点
- 当达到这个阈值点时, 就会变成固定(绝对)定位

sticky是相对于最近的滚动祖先包含滚动视口的( the nearest ancestor scroll container’s scrollport )

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .nav {
      background-color: #f00;
      color: #fff;

      /* position: relative;
      top: 0;
      left: 0;
      right: 0; */
      position: sticky;
      top: 0;
    }
  </style>
</head>
<body>

  <h1>我是标题</h1>
  <div class="nav">
    <span>电脑</span>
    <span>手机</span>
    <span>衣服</span>
    <span>鞋子</span>
  </div>
  <ul>
    <li>电脑列表1</li>
    <li>电脑列表2</li>
    <li>电脑列表3</li>
    <li>电脑列表4</li>
    <li>电脑列表5</li>
    <li>电脑列表6</li>
    <li>电脑列表7</li>
    <li>电脑列表8</li>
    <li>电脑列表9</li>
    <li>电脑列表10</li>
    <li>电脑列表11</li>
    <li>电脑列表12</li>
    <li>电脑列表13</li>
    <li>电脑列表14</li>
    <li>电脑列表15</li>
    <li>电脑列表16</li>
    <li>电脑列表17</li>
    <li>电脑列表18</li>
    <li>电脑列表19</li>
    <li>电脑列表20</li>
    <li>电脑列表21</li>
    <li>电脑列表22</li>
    <li>电脑列表23</li>
    <li>电脑列表24</li>
    <li>电脑列表25</li>
    <li>电脑列表26</li>
    <li>电脑列表27</li>
    <li>电脑列表28</li>
    <li>电脑列表29</li>
    <li>电脑列表30</li>
    <li>电脑列表31</li>
    <li>电脑列表32</li>
    <li>电脑列表33</li>
    <li>电脑列表34</li>
    <li>电脑列表35</li>
    <li>电脑列表36</li>
    <li>电脑列表37</li>
    <li>电脑列表38</li>
    <li>电脑列表39</li>
    <li>电脑列表40</li>
    <li>电脑列表41</li>
    <li>电脑列表42</li>
    <li>电脑列表43</li>
    <li>电脑列表44</li>
    <li>电脑列表45</li>
    <li>电脑列表46</li>
    <li>电脑列表47</li>
    <li>电脑列表48</li>
    <li>电脑列表49</li>
    <li>电脑列表50</li>
    <li>电脑列表51</li>
    <li>电脑列表52</li>
    <li>电脑列表53</li>
    <li>电脑列表54</li>
    <li>电脑列表55</li>
    <li>电脑列表56</li>
    <li>电脑列表57</li>
    <li>电脑列表58</li>
    <li>电脑列表59</li>
    <li>电脑列表60</li>
    <li>电脑列表61</li>
    <li>电脑列表62</li>
    <li>电脑列表63</li>
    <li>电脑列表64</li>
    <li>电脑列表65</li>
    <li>电脑列表66</li>
    <li>电脑列表67</li>
    <li>电脑列表68</li>
    <li>电脑列表69</li>
    <li>电脑列表70</li>
    <li>电脑列表71</li>
    <li>电脑列表72</li>
    <li>电脑列表73</li>
    <li>电脑列表74</li>
    <li>电脑列表75</li>
    <li>电脑列表76</li>
    <li>电脑列表77</li>
    <li>电脑列表78</li>
    <li>电脑列表79</li>
    <li>电脑列表80</li>
    <li>电脑列表81</li>
    <li>电脑列表82</li>
    <li>电脑列表83</li>
    <li>电脑列表84</li>
    <li>电脑列表85</li>
    <li>电脑列表86</li>
    <li>电脑列表87</li>
    <li>电脑列表88</li>
    <li>电脑列表89</li>
    <li>电脑列表90</li>
    <li>电脑列表91</li>
    <li>电脑列表92</li>
    <li>电脑列表93</li>
    <li>电脑列表94</li>
    <li>电脑列表95</li>
    <li>电脑列表96</li>
    <li>电脑列表97</li>
    <li>电脑列表98</li>
    <li>电脑列表99</li>
    <li>电脑列表100</li>
  </ul>

</body>
</html>
```

### 小案例

验证对最近的滚动祖先的视口进行粘性定位

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 500px;
      height: 500px;
      margin: 100px auto 0;
      overflow: scroll;
      background-color: #ccc;
    }

    .nav {
      background-color: #f00;
      color: #fff;
      position: sticky;
      top: 0;
    }
  </style>
</head>
<body>

  <div class="box">
    <h1>我是标题</h1>
    <div class="nav">
      <span>电脑</span>
      <span>手机</span>
      <span>衣服</span>
      <span>鞋子</span>
    </div>
    <ul>
      <li>电脑列表1</li>
      <li>电脑列表2</li>
      <li>电脑列表3</li>
      <li>电脑列表4</li>
      <li>电脑列表5</li>
      <li>电脑列表6</li>
      <li>电脑列表7</li>
      <li>电脑列表8</li>
      <li>电脑列表9</li>
      <li>电脑列表10</li>
      <li>电脑列表11</li>
      <li>电脑列表12</li>
      <li>电脑列表13</li>
      <li>电脑列表14</li>
      <li>电脑列表15</li>
      <li>电脑列表16</li>
      <li>电脑列表17</li>
      <li>电脑列表18</li>
      <li>电脑列表19</li>
      <li>电脑列表20</li>
      <li>电脑列表21</li>
      <li>电脑列表22</li>
      <li>电脑列表23</li>
      <li>电脑列表24</li>
      <li>电脑列表25</li>
      <li>电脑列表26</li>
      <li>电脑列表27</li>
      <li>电脑列表28</li>
      <li>电脑列表29</li>
      <li>电脑列表30</li>
      <li>电脑列表31</li>
      <li>电脑列表32</li>
      <li>电脑列表33</li>
      <li>电脑列表34</li>
      <li>电脑列表35</li>
      <li>电脑列表36</li>
      <li>电脑列表37</li>
      <li>电脑列表38</li>
      <li>电脑列表39</li>
      <li>电脑列表40</li>
      <li>电脑列表41</li>
      <li>电脑列表42</li>
      <li>电脑列表43</li>
      <li>电脑列表44</li>
      <li>电脑列表45</li>
      <li>电脑列表46</li>
      <li>电脑列表47</li>
      <li>电脑列表48</li>
      <li>电脑列表49</li>
      <li>电脑列表50</li>
      <li>电脑列表51</li>
      <li>电脑列表52</li>
      <li>电脑列表53</li>
      <li>电脑列表54</li>
      <li>电脑列表55</li>
      <li>电脑列表56</li>
      <li>电脑列表57</li>
      <li>电脑列表58</li>
      <li>电脑列表59</li>
      <li>电脑列表60</li>
      <li>电脑列表61</li>
      <li>电脑列表62</li>
      <li>电脑列表63</li>
      <li>电脑列表64</li>
      <li>电脑列表65</li>
      <li>电脑列表66</li>
      <li>电脑列表67</li>
      <li>电脑列表68</li>
      <li>电脑列表69</li>
      <li>电脑列表70</li>
      <li>电脑列表71</li>
      <li>电脑列表72</li>
      <li>电脑列表73</li>
      <li>电脑列表74</li>
      <li>电脑列表75</li>
      <li>电脑列表76</li>
      <li>电脑列表77</li>
      <li>电脑列表78</li>
      <li>电脑列表79</li>
      <li>电脑列表80</li>
      <li>电脑列表81</li>
      <li>电脑列表82</li>
      <li>电脑列表83</li>
      <li>电脑列表84</li>
      <li>电脑列表85</li>
      <li>电脑列表86</li>
      <li>电脑列表87</li>
      <li>电脑列表88</li>
      <li>电脑列表89</li>
      <li>电脑列表90</li>
      <li>电脑列表91</li>
      <li>电脑列表92</li>
      <li>电脑列表93</li>
      <li>电脑列表94</li>
      <li>电脑列表95</li>
      <li>电脑列表96</li>
      <li>电脑列表97</li>
      <li>电脑列表98</li>
      <li>电脑列表99</li>
      <li>电脑列表100</li>
    </ul>
  </div>

</body>
</html>
```

## 画布 和 视口

视口（Viewport）

- 文档的可视区域
- 如图红框所示

画布（Canvas）

- 用于渲染文档的区域
- 文档内容超出视口范围，可以通过滚动查看
- 如图黑框所示

宽高对比

- 画布 >= 视口

![](image/Pasted%20image%2020250521165510.png)

## 子绝父相

在绝大数情况下，子元素的绝对定位都是相对于父元素进行定位

如果希望子元素相对于父元素进行定位，又不希望父元素脱标，常用解决方案是

- 父元素设置position: relative（让父元素成为定位元素，而且父元素不脱离标准流）
- 子元素设置position: absolute
- 简称为“子绝父相”

## 将 position 设置为 absolute/fixed 元素（绝对定位元素）的特点

可以随意设置宽高

宽高默认由内容决定

不再受标准流的约束

- 不再严格按照从上到下、从左到右排布
- 不再严格区分块级(block)、行内级(inline)，行内块级(inline-block)的很多特性都会消失

不再给父元素汇报宽高数据

脱标元素内部默认还是按照标准流布局

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      background-color: #f00;
    }

    .box strong {
      position: absolute;
      width: 200px;
      height: 200px;
      background-color: #0f0;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <strong>
      <span>我是strong元素</span>
      <i>我是i元素</i>
    </strong>
  </div>

</body>
</html>
```

绝对定位元素（absolutely positioned element）

- position值为absolute或者fixed的元素

对于绝对定位元素来说

- 定位参照对象的宽度 = left + right + margin-left + margin-right + 绝对定位元素的实际占用宽度
- 定位参照对象的高度 = top + bottom + margin-top + margin-bottom + 绝对定位元素的实际占用高度

如果希望绝对定位元素的宽高和定位参照对象一样，可以给绝对定位元素设置以下属性

- left: 0
- right: 0
- top: 0
- bottom: 0
- margin:0

如果希望绝对定位元素在定位参照对象中居中显示，可以给绝对定位元素设置以下属性

- left: 0、right: 0、top: 0、bottom: 0、margin: auto
- 另外，还得设置具体的宽高值（宽高小于定位参照对象的宽高）

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 800px;
      height: 300px;
      background-color: #f00;
      position: relative;
    }

    /* 兼容性 */
    .container {
      height: 100px;
      background-color: #0f0;
      
      width: 200px;
      /* width: 100%; */
      position: absolute;
      left: 0;
      right: 0;
      top: 0;
      bottom: 0;
      margin: auto;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div class="container"></div>
  </div>

</body>
</html>
```

## auto 的含义

800 = 200 + margin-left: auto + margin-right: auto + left: 0 + right: 0

所以能水平和垂直居中，但是不推荐这样做

auto -> 交给浏览器你来出来

width: auto;

1. 行内非替换元素 -> width: 包裹内容
2. 块级元素 ->width: 包含块的宽度
3. 绝对定位元素 -> width: 包裹内容

## position 值对比

|          | 脱离标准流 | 定位元素 | 绝对定位元素 |                    定位参照对象                    |
| :------: | :---: | :--: | :----: | :------------------------------------------: |
|  static  |   ×   |  ×   |   ×    |                      ×                       |
| relative |   ×   |  √   |   ×    |                  元素自己原来的位置                   |
| absolute |   √   |  √   |   √    | 最邻近的定位祖先元素<br>（如果找不到这样的祖先元素，参照对象<br>是**视口**） |
|  fixed   |   √   |  √   |   √    |                      视口                      |

## z-index

 z-index属性用来设置定位元素的层叠顺序（仅对定位元素有效）

- 取值可以是正整数、负整数、0

比较原则

- 如果是兄弟关系

	- z-index越大，层叠在越上面
	- z-index相等，写在后面的那个元素层叠在上面

- 如果不是兄弟关系

	- 各自从元素自己以及祖先元素中，找出最邻近的2个定位元素进行比较
	- 而且这2个定位元素必须有设置z-index的具体数值

![](image/Pasted%20image%2020250521150113.png)

### 案例验证

- 非兄弟元素

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .item {
      position: fixed;
      width: 100px;
      height: 100px;
      left: 0;
      top: 0;
      background-color: #f00;
    }

    .box2 {
      left: 20px;
      top: 20px;
      background-color: #0f0;
      z-index: -1;
    }

    .box3 {
      left: 40px;
      top: 40px;
      background-color: #00f;
    }
  </style>
</head>
<body>
  
  <div class="item box1">1</div>
  <div class="container">
    <div class="item box2">2</div>
  </div>
  <div class="item box3">3</div>

</body>
</html>
```

- 兄弟元素

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .item {
      position: fixed;
      width: 100px;
      height: 100px;
      left: 0;
      top: 0;
      background-color: #f00;
    }

    .box2 {
      left: 20px;
      top: 20px;
      background-color: #0f0;
      z-index: -1;
    }

    .box3 {
      left: 40px;
      top: 40px;
      background-color: #00f;
    }

    .info {
      position: absolute;
      z-index: 999;
    }
  </style>
</head>
<body>
  
  <div class="item box1">1</div>
  <div class="container">
    <div class="item box2">
      <div class="info">哈哈哈</div>
      <div>呵呵呵</div>
    </div>
  </div>
  <div class="item box3">3</div>

</body>
</html>
```

# 浮动

## 认识浮动

float 属性可以指定一个元素应沿其容器的左侧或右侧放置，允许文本和内联元素环绕它。

- float 属性最初只用于在一段文本内浮动图像, 实现文字环绕的效果
- 但是早期的CSS标准中并没有提供好的左右布局方案, 因此在一段时间里面它成为网页多列布局的最常用工具

绝对定位、浮动都会让元素脱离标准流，以达到灵活布局的效果

可以通过float属性让元素产生浮动效果，float的常用取值

- none：不浮动，默认值
- left：向左浮动
- right：向右浮动

## 浮动规则

### 一

元素一旦浮动后, 脱离标准流

- 朝着向左或向右方向移动，直到自己的边界紧贴着包含块（一般是父元素）或者其他浮动元素的边界为止
- 定位元素会层叠在浮动元素上面

![](image/Pasted%20image%2020250522214549.png)

### 二

如果元素是向左（右）浮动，浮动元素的左（右）边界不能超出包含块的左（右）边界

![](image/Pasted%20image%2020250522213843.png)

<center>带圆圈的数字，标记着浮动元素浮动之前的位置</center>

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      margin: 0;
      overflow: 0;
    }

    .box {
      width: 200px;
      height: 200px;
      background-color: orange;
      margin: 0 auto;
      padding: 10px;
    }

    .item1, .item2 {
      background-color: #f00;
    }

    .item1 {
      /* 定位脱离标准流 */
      /* position: fixed;
      left: 0;
      top: 10px; */

      /* 脱离标准流 */
      float: left;
      background-color: #0f0;
    }

    .item2 {
      float: right;
    }
  </style>
</head>
<body>
  
  <div class="box">
    <div class="item1">1</div>
    <div class="item2">2</div>
  </div>

</body>
</html>
```

### 三

浮动元素之间不能层叠

- 如果一个元素浮动，另一个浮动元素已经在那个位置了，后浮动的元素将紧贴着前一个浮动元素（左浮找左浮，右浮找右浮）
- 如果水平方向剩余的空间不够显示浮动元素，浮动元素将向下移动，直到有充足的空间为止

![](image/Pasted%20image%2020250522214453.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>

    .container {
      width: 500px;
      height: 500px;
      background-color: orange;
    }

    .item {
      background-color: #f00;
      width: 100px;
      height: 100px;

      /* 三个全部向左浮动: 都会脱离标准流 */
      /* float: left; */
    }

    .box1 {
      float: left;
      background-color: #0f0;
      margin-left: 20px;
    }

    .box2 {
      float: left;
    }

    .box3 {
      float: left;
    }

    .box4 {
      width: 200px;
      height: 100px;
      background-color: purple;

      float: left;
    }
  </style>
</head>
<body>
  
  <!-- 浮动元素之间不能层叠 -->
  <div class="container">
    <div class="item box1">1</div>
    <div class="item box2">2</div>
    <div class="item box3">3</div>

    <div class="item box4">4</div>
  </div>

</body>
</html>
```

### 四

浮动元素不能与行内级内容层叠，行内级内容将会被浮动元素推出

- 比如行内级元素、inline-block元素、块级元素的文字内容

![](image/Pasted%20image%2020250522214418.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 1000px;
      height: 400px;
      background-color: orange;
    }

    .box strong {
      float: left;
      /* position: fixed;
      left: 0; */
    }
  </style>
</head>
<body>
  
  <div class="box">
    <span>我是span元素</span>
    <strong>我是strong元素</strong>
    <i>我也是i元素</i>
    <div>我是普通的内容</div>
  </div>

</body>
</html>
```

### 五

行内级元素、inline-block元素浮动后，其顶部将与所在行的顶部对齐

![](image/Pasted%20image%2020250522214337.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 500px;
      background: orange;
    }

    .box img {
      width: 300px;
      float: left;
    }
  </style>
</head>
<body>

  <div class="box">
    <img src="../images/kobe01.jpg" alt="">
    马俊宝从小热爱摄影，人生中第一部照相机是1978年买的海鸥相机，当时花了他将近半年的积蓄。从拿着相机的那一刻起，他就有一个梦想：把新疆最美的风景记录下来，让更多人看到。这个梦想在他年过半百的时候终于实现了。他的作品经常有爆款，不少视频有上亿观看量。留言里很多人赞叹新疆太美了，也有人不相信这些湖泊草原在新疆。马俊宝很开心：“我想做新疆美景的展示者，把新疆最美的一面展现给大家。”
    为了拍美食，张振新几乎跑遍了全疆，短视频的题材有大家熟悉的，也有粉丝留言推荐的，还有在网上搜索看到的。他会为了拍一种美食，乘飞机转汽车，辗转上千公里。从北疆的糖洋芋、土鸡焖饼子，再到南疆的鸽子汤、烤鱼、烤鸽子，每到一地，张振新都会和当地人聊天，听听当地人会去哪家老字号。他拍的店大多虽不起眼，但都是味道正宗、历久弥新的“宝藏店”。
  </div>

</body>
</html>
```

## 浮动练习

### 一

解决行内级元素、inline-block元素的水平间隙问题

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      /* font-size: 0; */
      /* display: flex; */
    }

    span {
      background-color: orange;
      /* font-size: 16px; */

      /* float: left;
      margin-right: 5px; */
    }
  </style>
</head>
<body>
  <!-- 
    将多个行内级元素中间的空格(间隙)去除的方法
      1. 删除换行符(不推荐)
      2. 将父级元素的font-size设置为0, 但是需要子元素设置回来
      3. 通过子元素(span)统一向一个方向浮动即可
      4. flex布局(还没有学习)
   -->
  
  <div class="box">
    <span>aaa</span>
    <span>bbb</span>
    <span>ccc</span>
  </div>

</body>
</html>
```

实现下面的布局

![](image/Pasted%20image%2020250522215712.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        /* 样式的重置 */
        ul, li {
            list-style: none;
            padding: 0;
            margin: 0;
        }

        a {
            text-decoration: none;
            color: #333;
        }

        /* 全局设置 */
        body {
            background-color: #f2f2f2;
        }

        /* 内容样式 */
        ul > li {
            float: left;
            margin-left: 12px;
        }

        ul > li > a {
            display: inline-block;
            width: 36px;
            height: 36px;
            text-align: center;
            line-height: 36px;
            border-radius: 6px;
            background-color: #fff;
            color: #3951b3;
            font-size: 14px;
        }

        ul > li > a:hover, ul > li.active > a {
            background-color: blue;
            color: #fff;
        }

        ul > li.next > a {
            width: 80px;
        }

    </style>
</head>
<body>

<!-- 结构: HTML -->
<ul>
    <li class="item"><a href="#">1</a></li>
    <li class="item"><a href="#">2</a></li>
    <li class="item"><a href="#">3</a></li>
    <li class="item"><a href="#">4</a></li>
    <li class="item active"><a href="#">5</a></li>
    <li class="item"><a href="#">6</a></li>
    <li class="item"><a href="#">7</a></li>
    <li class="item"><a href="#">8</a></li>
    <li class="item"><a href="#">9</a></li>
    <li class="item"><a href="#">10</a></li>
    <li class="item next"><a href="#">下一页 &gt;</a></li>
</ul>

</body>
</html>

```

### 二

实现京东页面下面的布局

![](image/Pasted%20image%2020250522215331.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    /* 公共的class */
    .content {
      width: 1190px;
      margin: 0 auto;
      background-color: orange;
      height: 800px;
    }

    /* 布局样式 */
    .box {
      /* margin: 0 -5px; */
      /* 3.方案三: 设置负的的margin(没有兼容性) */
      margin-right: -10px;
    }

    .item {
      width: 230px;
      height: 322px;
      background-color: purple;
      color: #fff;

      /* 浮动 */
      float: left;
      margin-right: 10px;
      /* margin: 0 5px; */
    }

    /* 1.有可能存在兼容性 */
    /* .item:nth-child(5n) {
      margin-right: 0;
    } */
    
    /* 2.麻烦一点点 */
    /* .item.last-item {
      margin-right: 0;
    } */
  </style>
</head>
<body>
  
  <div class="content">
    <div class="box">
      <div class="item item1">1</div>
      <div class="item item2">2</div>
      <div class="item item3">3</div>
      <div class="item item4">4</div>
      <div class="item item5">5</div>
    </div>
  </div>

</body>
</html>
```

这里解释一下第三种方式，我们的 box 盒子宽度是 auto 来源于父 content 盒子宽度 1190 px，但是 content 盒子要装下 5 个元素还少了 10 px，并且我们需要 1200 px 才能装下，但是也不想影响 content 盒子，我们可以使用 box 盒子包起来，设置 margin-right: -10px 这样就可以完美装下，因为这里涉及到 [盒子模型中盒子大小的计算](#box-sizing) ，1190px = margin-left + margin-right + padding-left + padding-right + box-width，所以盒子宽度被延伸了，因为默认是 auto

![](image/Pasted%20image%2020250522220919.png)

![](image/Pasted%20image%2020250522221006.png)

### 三

实现京东页面下面的布局

![](image/Pasted%20image%2020250522215506.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .content {
      width: 1190px;
      margin: 0 auto;
      background-color: #f00;
      height: 1000px;
    }

    .wrapper {
      margin-right: -10px;
    }

    .item {
      width: 290px;
      background-color: purple;
      margin-bottom: 10px;

      float: left;
      margin-right: 10px;
    }

    .item.left {
      height: 370px;
    }

    .item.right {
      height: 180px;
    }
  </style>
</head>
<body>
  
  <div class="content">
    <div class="wrapper">
      <div class="item left"></div>
      <div class="item left"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
    </div>
  </div>

</body>
</html>
```

### 四

实现考拉页面下面的布局

![](image/Pasted%20image%2020250522215523.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .content {
      width: 1100px;
      margin: 0 auto;
      height: 800px;
      background: #ccc;
    }

    .box {
      /* margin-left: 1px; */
    }

    .item {
      width: 221px;
      height: 168px;
      background: orange;
      color: #fff;

      float: left;

      border: 1px solid #000;
      /*这就是取消边框重叠*/
      margin-right: -1px;

      box-sizing: border-box;
    }

    .item.first {
      width: 220px;
    }
  </style>
</head>
<body>
<!--  最简单的方法就是给每个小盒子加边框，最外面的边框不用管-->
<!--边框重叠问题可以通过 margin 取负值来进行重叠，兄弟元素就是重叠，父子元素就是出来一点点-->
  <div class="content">
    <div class="box">
      <div class="item first">1</div>
      <div class="item">2</div>
      <div class="item">3</div>
      <div class="item">4</div>
      <div class="item">5</div>
    </div>
  </div>

</body>
</html>
```

## 浮动的问题 高度塌陷

由于浮动元素脱离了标准流，变成了脱标元素，所以不再向父元素汇报高度

- 父元素计算总高度时，就不会计算浮动子元素的高度，导致了高度坍塌的问题

解决父元素高度坍塌问题的过程，一般叫做清浮动（清理浮动、清除浮动）

清浮动的目的是

- 让父元素计算总高度的时候，把浮动子元素的高度算进去

如何清除浮动呢? 使用clear属性

### clear 属性

clear属性是做什么的

- clear 属性可以指定一个元素是否必须移动(清除浮动后)到在它之前的浮动元素下面

clear的常用取值

- left：要求元素的顶部低于之前生成的所有左浮动元素的底部
- right：要求元素的顶部低于之前生成的所有右浮动元素的底部
- both：要求元素的顶部低于之前生成的所有浮动元素的底部
- none：默认值，无特殊要求

- 那么我们可以利用这个特性来清除浮动

### 清浮动的方法

事实上我们有很多方法可以清除浮动

方法一: 给父元素设置固定高度

- 扩展性不好（不推荐）

方法二: 在父元素最后增加一个空的块级子元素，并且让它设置clear: both

- 会增加很多无意义的空标签，维护麻烦
- 违反了结构与样式分离的原则（不推荐）

方法三: 给父元素添加一个伪元素

- 推荐
- 编写好后可以轻松实现清除浮动

方法四：BFC

- 推荐，但是要明白原理

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .content {
      width: 1190px;
      margin: 0 auto;
      background: #f00;
    }

    .wrapper {
      margin-right: -10px;
    }

    .item {
      width: 290px;
      background-color: purple;
      margin-bottom: 10px;

      float: left;
      margin-right: 10px;
    }

    .item.left {
      height: 370px;
    }

    .item.right {
      height: 180px;
    }

    /* 其他的内容 */
    .other {
      height: 100px;
      background: #0f0;
    }

    .line {
      /* height: 10px; */
      /* background: blue; */
      clear: both;
    }

    /* 最终的解决方案 */
    .clear_fix::after {
      content: "";
      clear: both;
      /*因为伪元素默认是行内级元素，默认没有宽高*/
      display: block;

      /* 浏览器兼容 */
      visibility: hidden;
      height: 0;
    }

    .clear_fix {
      /* IE6/7 */
      *zoom: 1;
    }
  </style>
</head>
<body>

  <!-- 因为所有的后代item元素都是浮动的, 脱离标准流 -->
  <!-- 不会向父元素汇报高度, 那么content元素压根就没有高度 -->
  <div class="content">
    <div class="wrapper clear_fix">
      <div class="item left"></div>
      <div class="item left"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>

      <!-- <div class="line"></div> -->
    </div>
  </div>

  <div class="content">
    <div class="wrapper clear_fix">
      <div class="item left"></div>
      <div class="item left"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>
      <div class="item right"></div>

      <!-- <div class="line"></div> -->
    </div>
  </div>

  <!-- 我认为content没有高度, 那么我们就会直接在上面显示 -->
  <div class="other"></div>

</body>
</html>

```

## 布局方案总结

|            定位方案            | 应用场景 |
| :------------------------: | :--: |
|        normal flow         | 垂直布局 |
| absolute positioning（绝对定位） | 层叠布局 |
|         float（浮动）          | 水平布局 |

# flex 布局

## 认识flexbox

Flexbox翻译为弹性盒子:

- 弹性盒子是一种用于按行或按列布局元素的一维布局方法
- 元素可以膨胀以填充额外的空间, 收缩以适应更小的空间
- 通常我们使用Flexbox来进行布局的方案称之为flex布局(flex layout)

flex布局是目前web开发中使用最多的布局方案：

- flex 布局（Flexible 布局，弹性布局）、
- 目前特别在移动端可以说已经完全普及
- 在PC端也几乎已经完全普及和使用, 只有非常少数的网站依然在用浮动来布局

为什么需要flex布局呢?

- 长久以来，CSS 布局中唯一可靠且跨浏览器兼容的布局工具只有 floats 和 positioning
- 但是这两种方法本身存在很大的局限性, 并且他们用于布局实在是无奈之举

## 原先的布局存在的痛点

原来的布局存在哪些痛点

- 比如在父内容里面垂直居中一个块内容
- 比如使容器的所有子项等分可用宽度/高度，而不管有多少宽度/高度可用
- 比如使多列布局中的所有列采用相同的高度，即使它们包含的内容量不同

## flex 布局的出现

所以长久以来, 大家非常期待一种真正可以用于对元素布局的方案: 于是flex布局出现了

flexbox在使用时, 我们最担心的是它的兼容性问题:

- 可以在 caniuse 上查询到具体的兼容性

## flex布局的重要概念

两个重要的概念

- 开启了 flex 布局的元素叫 flex container
- flex container 里面的直接子元素叫做 flex item

当 flex container 中的子元素变成了flex item 时, 具备一下特点

- flex item 的布局将受 flex container 属性的设置来进行控制和布局
- flex item 不再严格区分块级元素和行内级元素
- flex item 默认情况下是包裹内容的, 但是可以设置宽度和高度

设置 display 属性为 flex 或者 inline-flex 可以成为 flex container

- flex： flex container 以 block-level 形式存在
- inline-flex： flex container 以 inline-level 形式存在

![](image/Pasted%20image%2020250523194152.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      /* flex: 块级盒子的flex-container */
      /* inline-flex: 了解, 行内级盒子的flex-container */
      display: flex;
      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <!-- aaaa -->
  <div class="box">
    <div class="item">1</div>
    <div class="item">2</div>
    <div class="item">3</div>
  </div>
  <!-- bbb -->

</body>
</html>
```

## flex布局的模型

![](image/Pasted%20image%2020250523194906.png)

## flex 相关的属性

应用在 flex container 上的 CSS 属性

- flex-flow
- flex-direction
- flex-wrap
- flex-flow
- justify-content
- align-items
- align-content

应用在 flex items 上的 CSS 属性

- flex-grow
- flex-basis
- flex-shrink
- order
- align-self
- flex

### flex container

#### flex-direction

flex items 默认都是沿着 main axis（主轴）从 main start 开始往 main end 方向排布

- flex-direction 决定了 main axis 的方向，有 4 个取值
- row（默认值）、row-reverse、column、column-reverse

![](image/Pasted%20image%2020250523200107.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;

      /* 修改主轴的方向 */
      /* row-reverse: row的反转 */
      /* column: 列变成主轴的方向 */
      /* column-reverse: 列主轴进行反转 */
      /* flex-direction: column-reverse; */
    }

    .item {
      width: 120px;
      height: 120px;

      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex-wrap

 flex-wrap 决定了 flex container 是单行还是多行

- nowrap（默认）：单行
- wrap：多行、
- wrap-reverse：多行（对比 wrap，cross start 与 cross end 相反）

![](image/Pasted%20image%2020250523200909.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;

      /* nowrap: 默认值不换行 */
      /* flex-wrap: wrap; */
      /* flex-flow: wrap; */
      flex-flow: row-reverse wrap;
    }

    .item {
      width: 120px;
      height: 120px;

      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex-flow

flex-flow 属性是 flex-direction 和 flex-wrap 的简写。

- 顺序任意，并且都可以省略

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;

      /* flex-direction: row-reverse;
      flex-wrap: wrap-reverse; */
      flex-flow: row-reverse wrap-reverse;
    }

    .item {
      width: 120px;
      height: 120px;

      background-color: #f00;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### justify-content

justify-content 决定了 flex items 在 main axis 上的对齐方式

- flex-start（默认值）
	- 与 main start 对齐

- flex-end
	- 与 main end 对齐

- center
	- 居中对齐

- space-between
	- flex items 之间的距离相等
	- 与 main start、main end 两端对齐

- space-around
	- flex items 之间的距离相等
	- flex items 与 main start、main end 之间的距离是 flex items 之间距离的一半

- space-evenly
	- flex items 之间的距离相等
	- flex items 与 main start、main end 之间的距离 等于 flex items 之间的距离

![](image/Pasted%20image%2020250523201028.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;
      /* padding: 0 10px; */
      box-sizing: border-box;

      display: flex;

      flex-wrap: wrap;

      /* 切换justify-content */
      /* flex-end: 让元素和main end对齐 */
      /* center: 居中对齐 */
      /* space-between: 两端个放一个元素, 其他多余的元素一定要空间等分 */
      /* space-evenly: 两端也有间距, 并且所有的空间进行等分 */
      /* space-around: 两端也有间距, 两端的间距是items之间的间距一半 */
      justify-content: space-between;
    }

    .item {
      width: 120px;
      height: 120px;

      background-color: #f00;

      /* margin-left: 20px; */
      /* margin: 0 20px; */
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
    <div class="item item4">4</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### align-item

align-items 决定了 flex items 在 cross axis 上的对齐方式

- normal
	- 在弹性布局中，效果和 stretch 一样

- stretch
	- 当 flex items 在 cross axis 方向的 size 为 auto 时，会自动拉伸至填充 flex container

- flex-start
	- 与 cross start 对齐

- flex-end
	- 与 cross end 对齐

- center
	- 居中对齐

- baseline
	- 与基准线对齐

![](image/Pasted%20image%2020250523201559.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;
      /* padding: 0 10px; */
      box-sizing: border-box;

      display: flex;

      align-items: stretch;
    }

    .item {
      width: 120px;
      /* height: 120px; */
    }

    .item1 {
      height: 80px;
      font-size: 30px;
    }

    .item2 {
      height: 150px;
      font-size: 40px;
    }

    .item3 {
      height: 60px;
      font-size: 12px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1x</div>
    <div class="item item2">2x</div>
    <div class="item item3">3x</div>
    <div class="item item4">4x</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### align-content

align-content 决定了多行 flex items 在 cross axis 上的对齐方式，用法与 justify-content 类似

- stretch（默认值）
	- 与 align-items 的 stretch 类似

- flex-start
	- 与 cross start 对齐

- flex-end
	- 与 cross end 对齐

- center
	- 居中对齐

- space-between
	- flex items 之间的距离相等
	- 与 cross start、cross end两端对齐

- space-around
	- flex items 之间的距离相等
	- flex items 与 cross start、cross end 之间的距离是 flex items 之间距离的一半

- space-evenly
- flex items 之间的距离相等
- flex items 与 cross start、cross end 之间的距离 等于 flex items 之间的距离

![](image/Pasted%20image%2020250523202749.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
      flex-wrap: wrap;

      justify-content: space-between;
      align-content: center;
    }

    .item {
      width: 120px;
      height: 120px;
      /* margin-bottom: 10px; */
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1x</div>
    <div class="item item2">2x</div>
    <div class="item item3">3x</div>
    <div class="item item4">4x</div>
    <div class="item item2">2x</div>
    <div class="item item3">3x</div>
    <div class="item item4">4x</div>
    <div class="item item2">2x</div>
    <div class="item item3">3x</div>
    <div class="item item4">4x</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

###  flex items

#### order

order 决定了 flex items 的排布顺序

- 可以设置任意整数（正整数、负整数、0），值越小就越排在前面
- 默认值是 0

![](image/Pasted%20image%2020250523202932.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
    }

    .item {
      width: 120px;
      height: 120px;
    }

    .item1 {
      order: 5;
    }

    .item2 {
      order: 3;
    }

    .item3 {
      order: 9;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### align-self

flex items 可以通过 align-self 覆盖 flex container 设置的 align-items

- auto（默认值）：遵从 flex container 的 align-items 设置
- stretch、flex-start、flex-end、center、baseline，效果跟 align-items 一致

![](image/Pasted%20image%2020250523203011.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;

      align-items: center;
    }

    .item {
      width: 120px;
      height: 120px;
    }

    .item1 {
      height: 90px;
    }

    .item2 {
      height: 150px;

      align-self: flex-start;
    }

    .item3 {
      height: 120px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex-grow

flex-grow 决定了 flex items 如何扩展(拉伸/成长)

- 可以设置任意非负数字（正小数、正整数、0），默认值是 0
- 当 flex container 在 main axis 方向上有剩余 size 时，flex-grow 属性才会有效

如果所有 flex items 的 flex-grow 总和 sum 超过 1，每个 flex item 扩展的 size 为

- flex container 的剩余 size *  flex-grow / sum

flex items 扩展后的最终 size 不能超过 max-width \ max-height

![](image/Pasted%20image%2020250523203214.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
    }

    .item {
      width: 120px;
      height: 120px;

      flex-grow: 0;
    }

    .item1 {
      flex-grow: 1;
      max-width: 150px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex-shrink

flex-shrink 决定了 flex items 如何收缩(缩小)

- 可以设置任意非负数字（正小数、正整数、0），默认值是 1
- 当 flex items 在 main axis 方向上超过了 flex container 的 size，flex-shrink 属性才会有效

如果所有 flex items 的 flex-shrink 总和超过 1，每个 flex item 收缩的 size为 flex items 超出 flex container 的 size * 收缩比例 / 所有 flex items 的收缩比例之和

flex items 收缩后的最终 size 不能小于 min-width\min-height

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
    }

    .item {
      width: 120px;
      height: 120px;

      flex-shrink: 0;
    }

    .item1, .item2 {
      flex-shrink: 1;
    }

    .item1 {
      min-width: 100px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
    <div class="item item4">4</div>
    <div class="item item5">5</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex-basis

flex-basis 用来设置 flex items 在 main axis 方向上的 base size

- auto（默认值）、具体的宽度数值（100px）

决定 flex items 最终 base size 的因素，从优先级高到低

- max-width\max-height\min-width\min-height
- flex-basis
- width \ height
- 内容本身的 size

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
    }

    .item {
      width: 120px;
      /* 基础尺寸 */
      flex-basis: 120px;
      height: 120px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2我是han_hahahaha</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

#### flex属性

flex 是 flex-grow || flex-shrink || flex-basis 的简写, flex 属性可以指定 1 个，2 个或 3 个值

单值语法:

- 值必须为以下其中之一
- 一个无单位数(`<number>`): 它会被当作`<flex-grow>`的值
- 一个有效的宽度(width)值: 它会被当作 `<flex-basis>`的值。
- 关键字none，auto或initial.

双值语法

- 第一个值必须为一个无单位数，并且它会被当作` <flex-grow>` 的值
- 第二个值必须为以下之一
	- 一个无单位数：它会被当作 `<flex-shrink> `的值
	- 一个有效的宽度值: 它会被当作 `<flex-basis>` 的值

三值语法

- 第一个值必须为一个无单位数，并且它会被当作` <flex-grow>` 的值
- 第二个值必须为一个无单位数，并且它会被当作 `<flex-shrink>` 的值
- 第三个值必须为一个有效的宽度值， 并且它会被当作 `<flex-basis>` 的值

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      height: 500px;
      background-color: orange;

      display: flex;
    }

    .item {
      width: 120px;
      height: 120px;

      /* flex-grow flex-shrink flex-basis */
      /* none: 0 0 auto */
      /* auto: 1 1 auto */
      flex: 1 1 10px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2我是coderwhy_why_hahahaha</div>
    <div class="item item3">3</div>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

## 思考：如下布局如何解决对其问题

在网页中经常会有多行布局，这个时候 flex 布局就会不太好用了，在使用 space-between，这个时候多列就会有排布问题

1. 通过计算设置 margin，再通过 nth-child 来设置，这种很笨，当宽度发生改变，所有的都需要重新计算
2. 加点没有高度的盒子占位不就行了，行内非替换元素没有内容就没有高度，设置宽度就好了

![](image/Pasted%20image%2020250523200737.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      width: 500px;
      background-color: orange;

      display: flex;
      flex-wrap: wrap;
      justify-content: space-between;
    }

    .item {
      width: 110px;
      height: 140px;

      /* margin-right: 20px; */
    }

    .container > i {
      width: 110px;
    }

    /* .item:nth-child(4n) {
      margin-right: 0;
    } */
  </style>
</head>
<body>
  
  <div class="container">
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
    <div class="item item1">1</div>
    <div class="item item2">2</div>
    <div class="item item3">3</div>
    <div class="item item3">3</div>
    <!-- 添加span的个数是列数减-2 -->
   <i></i><i></i>
  </div>

  <script src="./js/itemRandomColor.js"></script>
</body>
</html>
```

# 形变和动画

## transform

CSS transform 属性允许你旋转，缩放，倾斜或平移给定元素。

Transform是形变的意思，transformer就是变形金刚

常见的函数 transform function有

- 平移：translate(x, y)
- 缩放：scale(x, y)
- 旋转：rotate(deg)
- 倾斜：skew(deg, deg)

通过上面的几个函数，我们可以改变某个元素的形变

### translate

平移：translate(x, y)

值个数

- 一个值时，设置x轴上的位移
- 二个值时，设置x轴和y轴上的位移

值类型

- 数字：100px
- 百分比：参照元素本身（ refer to the size of bounding box ）

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      display: inline-block;
      border: 5px solid #f00;
    }

    .container .box {
      width: 200px;
      height: 200px;
      background-color: orange;

      transform: translate(100px, 100px);
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>

</body>
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      display: inline-block;
      border: 5px solid #f00;
    }

    .container .box {
      width: 200px;
      height: 100px;
      background-color: orange;

      /* 百分比: 你的百分比是相对于谁? */
      /* 不同地方的百分比相对参照物是不一样 */

      /* traslate的百分比是相对于自身的 */
      /* 如果设置的x位移: 那么参考的是自身的宽度 */
      /* 如果设置的y位移: 那么参考的是自身的高度 */
      transform: translate(100%, 100%);

      /* transform: translate(x, y); */
      /* transform: translateX();
      transform: translateY(); */
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>

</body>
</html>
```

### scale

缩放：scale(x, y)

值个数

- 一个值时，设置x轴上的缩放
- 二个值时，设置x轴和y轴上的缩放

值类型

- 数字
	- 1：保持不变
	- 2：放大一倍
	- 0.5：缩小一半

- 百分比：不支持百分比

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      text-align: center;
      padding-top: 200px;
    }

    .container {
      display: inline-block;
      border: 20px solid #f00;
    }

    .box {
      border: 20px solid #0f0;
      width: 200px;
      height: 200px;
      background-color: orange;

      /* 形变 */
      transform: scale(60%, 60%);
    }

    .box1 {
      border: 20px solid #0f0;
      width: 200px;
      height: 200px;
      background-color: purple;

      /* 形变 */
      /* 0~1 对元素进行缩小 */
      /* 大于1 对元素进行放大 */
      /* transform: scale(1.2, 1.2); */
    }

    .box1:hover {
      transform: scale(1.1, 1.1);
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>
  
  <div class="container">
    <div class="box1"></div>
  </div>

</body>
</html>
```

### rotate

旋转：rotate(deg)

值个数

- 一个值时，表示旋转的角度

值类型

- deg：旋转的角度
	- 正数为顺时针
	- 负数为逆时针

注意：旋转的原点受transform-origin的影响

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      text-align: center;
      padding-top: 200px;
    }

    .container {
      display: inline-block;
      border: 10px solid #f00;
    }

    .box {
      width: 200px;
      height: 100px;
      background-color: orange;
    }

    .box:hover {
      transform: rotate(-45deg);
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>

</body>
</html>
```

### transform-origin

transform-origin：变形的原点

一个值

- 设置 x 轴的原点

两个值

- 设置 x 轴和 y 轴的原点

必须是`<length>`，`<percentage>`，或 left, center, right, top, bottom 关键字中的一个

- left, center, right, top, bottom 关键字
- length：从左上角开始计算
- 百分比：参考元素本身大小

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    body {
      text-align: center;
      padding-top: 200px;
    }

    .container {
      display: inline-block;
      border: 10px solid #f00;
    }

    .box {
      width: 200px;
      height: 100px;
      background-color: orange;

      /* 修改当前元素的形变的原点位置 */
      /* transform-origin: center top; */
      /* transform-origin: 20px 20px; */
      transform-origin: 10% 10%;
    }

    .box:hover {
      transform: rotate(45deg) scale(0.5);
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>

</body>
</html>
```

### skew

旋转：skew(x, y)

值个数

- 一个值时，表示 x 轴上的倾斜
- 二个值时，表示 x 轴和 y 轴上的倾斜

值类型

- deg：旋转的角度
- 正数为顺时针
- 负数为逆时针

注意：旋转的原点受 transform-origin 的影响

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      font-style: italic;
      width: 200px;
      height: 100px;
      background-color: orange;
    }

    .box:hover {
      transform: skew(10deg, 10deg);
    }
  </style>
</head>
<body>
  
  <div class="box">我是div元素</div>

</body>
</html>
```

### transition 过渡动画

transition CSS 属性是 

- transition-property
- transition-duration
- transition-timing-function 
- transition-delay 

的一个简写属性

transition-property：指定应用过渡属性的名称

- 可以写 all 表示所有可动画的属性
- 属性是否支持动画查看文档

transition-duration：指定过渡动画所需的时间

- 单位可以是秒（s）或毫秒（ms）

transition-timing-function：指定动画的变化曲线

- https://developer.mozilla.org/zh-CN/docs/Web/CSS/transition-timing-function

transition-delay：指定过渡动画执行之前的等待时间

这是设置多个值的小案例

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 200px;
      height: 100px;
      background-color: orange;
    }

    .box:hover {
      /* transform: translateX(50px);
      transform: scale(1.2);
      transform: rotate(45deg); */

      /* 
        <transform-function>+
          +: 一个或者多个, 并且多个之间以空格分隔
          transform: scale() translate();

        <box-shadow>#
          #: 一个或者多个, 多个之间以, 分隔
          box-shadow: 1px 1px 1px 1px #f00, 
      */
      transform: translate(50px) scale(1.2) rotate(45deg);
    }
  </style>
</head>
<body>
  
  <div class="box"></div>

</body>
</html>
```

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .container {
      background-color: #f00;
    }

    .box {
      position: relative;
      left: 0;

      width: 200px;
      height: 100px;
      background-color: orange;

      /* 告知浏览器 box 在进行一些CSS属性变化的时候有一个过渡效果 */
      /* transition-property: transform, left; */
      /* transition-property: all;
      transition-duration: 1s;
      transition-timing-function: ease-in;
      transition-delay: 1s; */
      
      /* 简写属性 */
      transition: all 1s ease-in 1s;
    }

    .container:hover .box {
      left: 100px;
      transform: translate(100px);
      width: 500px;
    }
  </style>
</head>
<body>
  
  <div class="container">
    <div class="box"></div>
  </div>

</body>
</html>
```

## 关键帧动画

之前通过 transition 来进行过渡动画，但是过渡动画只能控制首尾两个值

从关键帧动画的角度相当于只是定义了两帧的状态：第一帧和最后一帧

- 如果我们希望可以有更多状态的变化，可以直接使用关键帧动画。

关键帧动画使用 @keyframes 来定义多个变化状态，并且使用 animation-name 来声明匹配

- 使用 @keyframes创建一个规则
- @keyframes中使用百分比定义各个阶段的样式
- 通过animation将动画添加到属性上

另外，也可以使用from和to关键字

- from相当于0%
- to相当于100%

## CSS animation属性

CSS animation 属性是 

- animation-name
- animation-duration
- animation-timing-function
- animation-delay
- animation-iteration-count
- animation-direction
- animation-fill-mode
- animation-play-state 

属性的一个简写属性形式

- animation-name：指定执行哪一个关键帧动画

- animation-duration：指定动画的持续时间

- animation-timing-function：指定动画的变化曲线

- animation-delay：指定延迟执行的时间

- animation-iteration-count：指定动画执行的次数，执行infinite表示无限动画

- animation-direction：指定方向，常用值normal和reverse

- animation-fill-mode：执行动画最后保留哪一个值
	- none：回到没有执行动画的位置
	- forwards：动画最后一帧的位置
	- backwards：动画第一帧的位置

- animation-play-state：指定动画运行或者暂停（在JavaScript中使用，用于暂停动画）

```html
<!DOCTYPE html>
<html lang="en">
<head>
  <meta charset="UTF-8">
  <meta http-equiv="X-UA-Compatible" content="IE=edge">
  <meta name="viewport" content="width=device-width, initial-scale=1.0">
  <title>Document</title>
  <style>
    .box {
      width: 200px;
      height: 100px;
      background-color: orange;

      /* box要执行moveAnim的动画 */
      animation-name: moveAnim;
      animation-duration: 3s;
      animation-timing-function: ease-in-out;

      /* 其他属性: */
      /* 动画执行的次数 */
      /* animation-delay: 2s; */
      /* animation-iteration-count: 2; */
      /* animation-direction: reverse; */
      /* 元素停留在动画的哪一个位置 */
      /* animation-fill-mode: forwards; */

      /* js动态修改 */
      /* animation-play-state: paused; */
      animation: moveAnim 3s linear 1s 2 normal forwards, ;
    }

    @keyframes moveAnim {
      0% {
        transform: translate(0, 0) scale(0.5, 0.5);
      }

      33% {
        transform: translate(0, 200px) scale(1.2, 1.2);
      }

      66% {
        transform: translate(400px, 200px) scale(1, 1);
      }

      100% {
        transform: translate(400px, 0) scale(0.5, 0.5);
      }
    }

  </style>
</head>
<body>
  
  <div class="box">

  </div>

</body>
</html>
```