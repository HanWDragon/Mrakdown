## grid网格概念

![](image/Pasted%20image%2020230910225916.png)

![](image/Pasted%20image%2020230910225940.png)

![](image/Pasted%20image%2020230910230016.png)

## grid容器

![](image/Pasted%20image%2020230910231428.png)

### 定义网格与fr单位

![](image/Pasted%20image%2020230910231536.png)

![](image/Pasted%20image%2020230910231829.png)

- fr很像flex里面的flex-shrink和flex-grow，这个是一个比例值

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            /* grid-template-columns: 50px 50px 50px;
            grid-template-rows: 50px 50px 50px; */

            /* grid-template-columns: 50px 20% auto;
            grid-template-rows: 50px 50px; */

            grid-template-columns: 150px 1fr 1fr;
            grid-template-rows: 0.3fr 0.3fr;
        }
        .main div{
            background:pink;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
        <div>5</div>
        <div>6</div>
    </div>
</body>
</html>
```

### 合并网格与网格命名

![](image/Pasted%20image%2020230910232632.png)

![](image/Pasted%20image%2020230910233500.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        /* .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
            grid-template-areas: 
            "a1 a1 a2"
            "a1 a1 a2"
            "a3 a3 a3";
        }
        .main div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }
        .main div:nth-of-type(1){
            grid-area: a1;
        }
        .main div:nth-of-type(2){
            grid-area: a2;
        }
        .main div:nth-of-type(3){
            grid-area: a3;
        } */

        /* .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
            grid-template-areas: 
            "a1 a2 a3";
        }
        .main div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }
        进行位置调换后，其他的单元格并不会空着，会自动填充到别的位置
        .main div:nth-of-type(1){
            grid-area: a3;
        } */

        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            /* grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
            grid-template-areas: 
            "a1 a1 a2"
            "a1 a1 a2"
            "a3 a3 a3"; */
            grid-template: 
            "a1 a1 a2" 1fr
            "a1 a1 a2" 1fr 
            "a3 a3 a3" 1fr
            / 1fr 1fr 1fr;
        }
        .main div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }
        .main div:nth-of-type(1){
            grid-area: a1;
        }
        .main div:nth-of-type(2){
            grid-area: a2;
        }
        .main div:nth-of-type(3){
            grid-area: a3;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
    </div>
</body>
</html>
```

### 网格间隙及简写

![](image/Pasted%20image%2020230910233725.png)


- 既能给弹性布局使用也可以给网格布局使用

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
            grid-template-areas: 
            "a1 a1 a2"
            "a1 a1 a2"
            "a3 a3 a3";
            /* grid-row-gap: 20px;
            grid-column-gap: 30px; */
            /* grid-gap: 20px 30px; */
            /* row-gap: 20px;
            column-gap: 30px; */
            gap:20px 30px;
        }
        .main div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }
        .main div:nth-of-type(1){
            grid-area: a1;
        }
        .main div:nth-of-type(2){
            grid-area: a2;
        }
        .main div:nth-of-type(3){
            grid-area: a3;
        }

        .main2{
            width:300px;
            background:skyblue;
            display: flex;
            flex-wrap: wrap;
            row-gap: 20px;
            column-gap: 30px;
        }
        .main2 div{
            width:100px;
            height:100px;
            background:pink;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
    </div>
    <div class="main2">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
        <div>5</div>
    </div>
</body>
</html>
```

### 网格对齐方式及其简写

![](image/Pasted%20image%2020230910234322.png)

![](image/Pasted%20image%2020230910234657.png)

- item属性是内容小于单元格进行设置
- content是单元格小于容器进行的设置

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 100px 100px 100px;
            grid-template-rows: 100px 100px 100px;
            /* justify-items: start;
            align-items: end; */
            place-items: end start;
        }
        .main div{
            width:50px;
            height:50px;
            background:pink;
        }

        .main2{
            width:500px;
            height:500px;
            background:skyblue;
            display: grid;
            grid-template-columns: 100px 100px 100px;
            grid-template-rows: 100px 100px 100px;
            /* justify-content: space-evenly;
            align-content: end; */
            place-content: end space-evenly;
        }
        .main2 div{
            background:pink;
        }
    </style>
</head>
<body>
    <div class="main">
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

    <div class="main2">
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
</html>
```

### 显式网格与隐式网格

![](image/Pasted%20image%2020230910235234.png)

- 网格比子项要少就会产生隐式网格

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            /* grid-template-columns: 100px 100px 100px;
            grid-template-rows: 100px; */
            /* 默认：row 就是行产生隐式网格 */
            /* grid-auto-flow: row; */
            /* 可以调节产生隐式网格的高度 */
            /* grid-auto-rows: 100px; */

            grid-template-columns: 100px;
            grid-template-rows: 100px 100px 100px;
            /* column 就是列产生隐式网格 */
            grid-auto-flow: column;
            /* 可以调节产生隐式网格的宽度 */
            grid-auto-columns: 100px;
        }
        .main div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }

        .main2{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 100px 100px 100px;
            grid-template-rows: 100px;
            grid-auto-flow: row dense;  /* dense 紧密的 */
            grid-auto-rows: 100px;
        }
        .main2 div{
            background:pink;
            border:1px black solid;
            box-sizing: border-box;
        }
        .main2 div:nth-of-type(1){
            grid-column-start: 2;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
        <div>5</div>
    </div>
    <hr>
    <div class="main2">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
        <div>5</div>
    </div>
</body>
</html>
```

### repeat()和minmax()

![](image/Pasted%20image%2020230911091626.png)



```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            height:400px;
            background:skyblue;
            display: grid;
            /* grid-template-columns: 100px 100px 100px; */
            /* grid-template-columns: repeat(3, 100px); */
            /* grid-template-columns: 150px 100px 100px; */
            /* grid-template-columns: 150px repeat(2, 100px); */
            /*这个参数根据网格大小自动控制网格个数*/
            grid-template-columns: repeat(auto-fill, 100px);
            grid-template-rows: 100px;
        }
        .main div{
            background:pink;
            
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
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
        .main{
            height:400px;
            background:skyblue;
            display: grid;
            /*这样中间的子元素就可以自适应宽度，占据剩下的宽度，但是最小值是内容*/
            /* grid-template-columns: 100px 1fr 100px; */
            grid-template-columns: 100px minmax(100px, 1fr) 100px;
            grid-template-rows: 100px;
        }
        .main div{
            background:pink;
            border:1px black solid;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
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
        .main{
            height:400px;
            background:skyblue;
            display: grid;
            /*这样中间的子元素就可以自适应宽度，占据剩下的宽度，但是最小值是内容*/
            /* grid-template-columns: 100px 1fr 100px; */
            grid-template-columns: 100px minmax(100px, 1fr) 100px;
            grid-template-rows: 100px;
        }
        .main div{
            background:pink;
            border:1px black solid;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
    </div>
</body>
</html>
```


## grid子项

![](image/Pasted%20image%2020230910231440.png)

### 基于线的元素放置

![](image/Pasted%20image%2020230911000427.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: 1fr 1fr 1fr;
            grid-template-rows: 1fr 1fr 1fr;
        }
        .main div:nth-of-type(1){
            background:pink;
            grid-column-start: 2;
            grid-column-end: 3;
            /* 默认值：auto 会自动将元素往后面进行排列
            设置这个值后，这个元素就有了确切的位置，后面的元素会对空余进行补充
            */
             grid-row-start: 2;
            grid-row-end: 3; 
        }
        .main div:nth-of-type(2){
            background:slategray;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
    </div>
</body>
</html>
```

![](image/Pasted%20image%2020230911084400.png)

![](image/Pasted%20image%2020230911084951.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            /*可以在网格定义的时候完成命名*/
            grid-template-columns:[col1] 1fr [col2] 1fr [col3] 1fr [col4];
            grid-template-rows:[row1] 1fr [row2] 1fr [row3] 1fr [row4];
        }
        .main div:nth-of-type(1){
            width:50px;
            height:50px;
            background:pink;
            justify-self: center;
            align-self: center;
            /*span代表占据的个数*/
            /* grid-column-start:2;
            grid-column-end:span 2; */
           /*  grid-column-start: col2;
            grid-column-end: col4; */

            /* grid-column: 2 / 3; = grid-column-start:2; + grid-column-end:span 3;
            grid-row: 2 / 4; = grid-row-start: 2; + grid-row-end: 4; */
            grid-area: 2 / 2 / 3 / 3;
           
        }
        .main div:nth-of-type(2){
            background:slategray;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
    </div>
</body>
</html>
```

### 子项对齐方式

![](image/Pasted%20image%2020230911085332.png)

## 比定位更加方便的叠加布局

![](image/Pasted%20image%2020230911093055.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width: 530px;
            height: 300px;
            background:skyblue;
            display: grid;
        }
        .main img{
            /*设置位置*/
            grid-area: 1/1/1/1;
        }
        /*和图片处在同一网格*/
        .main span{
            grid-area: 1/1/1/1;
            color: orangered;
            /*设置在网格中的位置*/
            justify-self: end;
            border: 1px orangered solid;
            height: 20px;
            text-align: center;
            line-height: 20px;
            margin:5px;
        }
        .main p{
            grid-area: 1/1/1/1;
            align-self: end;
            text-align: center;
            margin:0;
            padding:0;
            background:rgba(0,0,0,0.5);
            height:30px;
            line-height: 30px;
            color:white;
        }
    </style>
</head>
<body>
    <div class="main">
        <img src="./phone.png" alt="">
        <span>最新款</span>
        <p>手机热卖中.....</p>
    </div>
</body>
</html>
```

## 多种组合排列布局

![](image/Pasted%20image%2020230911104205.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .main{
            width:300px;
            height:300px;
            background:skyblue;
            display: grid;
            grid-template-columns: repeat(3,1fr);
            grid-template-rows: repeat(3,1fr);
            gap:5px;
        }
        .main div{
            background:pink;
        }
        .main div:nth-of-type(1){
            /* grid-area: 1/1/span 2/span 2; */
            grid-area: 2/1/span 2/span 2;
        }
    </style>
</head>
<body>
    <div class="main">
        <div>1</div>
        <div>2</div>
        <div>3</div>
        <div>4</div>
        <div>5</div>
        <div>6</div>
    </div>
</body>
</html>
```

## 栅格布局

![](image/Pasted%20image%2020230911123013.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <style>
        .row{
            background:skyblue;
            display: grid;
            grid-template-columns: repeat(12, 1fr);
            grid-template-rows: 50px;
            grid-auto-rows: 50px;
        }
        .row div{
            background:pink;
            border:1px black solid;
        }
        /*这样书写是为了省下的元素自动填充空余位置*/
        .row .col-1{
            grid-area: auto/auto/auto/span 1;
        }
        .row .col-2{
            grid-area: auto/auto/auto/span 2;
        }
        .row .col-3{
            grid-area: auto/auto/auto/span 3;
        }
        .row .col-4{
            grid-area: auto/auto/auto/span 4;
        }
        .row .col-5{
            grid-area: auto/auto/auto/span 5;
        }
        .row .col-6{
            grid-area: auto/auto/auto/span 6;
        }
        .row .col-7{
            grid-area: auto/auto/auto/span 7;
        }
        .row .col-8{
            grid-area: auto/auto/auto/span 8;
        }
        .row .col-9{
            grid-area: auto/auto/auto/span 9;
        }
        .row .col-10{
            grid-area: auto/auto/auto/span 10;
        }
        .row .col-11{
            grid-area: auto/auto/auto/span 11;
        }
        .row .col-12{
            grid-area: auto/auto/auto/span 12;
        }
    </style>
</head>
<body>
    <div class="row">
        <div class="col-6">1</div>
        <div class="col-3">2</div>
        <div class="col-4">3</div>
        <div class="col-5">4</div>
    </div>
</body>
</html>
```

## 容器自适应行列布局

![](image/Pasted%20image%2020230911124515.png)

## 综合案例-百度热词风云榜

![](image/Pasted%20image%2020230911131221.png)

```html
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta http-equiv="X-UA-Compatible" content="IE=edge">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Document</title>
    <link rel="stylesheet" href="./reset.css">
    <style>
        .top{
            width:308px;
            border:1px #dadadc solid;
            /*居中*/
            margin:20px auto;
        }
        .top-title{
            height:30px;
            display: flex;
            align-items: center;
            margin-left:15px;
            font-size:14px;
            font-weight: bold;
        }
        .top-list{
            height:352px;
            margin: 0 14px;
            display: grid;
            grid-template-columns: repeat(3, 1fr);
            grid-template-rows: repeat(4, 1fr);
            grid-template-areas: 
            "a1 a3 a3"
            "a2 a3 a3"
            "a4 a4 a5"
            "a6 a7 a7";
            gap:8px;
        }
        .top-list div:nth-of-type(1){
            grid-area: a1;
        }
        .top-list div:nth-of-type(2){
            grid-area: a2;
        }
        .top-list div:nth-of-type(3){
            grid-area: a3;
        }
        .top-list div:nth-of-type(4){
            grid-area: a4;
        }
        .top-list div:nth-of-type(5){
            grid-area: a5;
        }
        .top-list div:nth-of-type(6){
            grid-area: a6;
        }
        .top-list div:nth-of-type(7){
            grid-area: a7;
        }

        .top-list a{
            width:100%;
            height:100%;
            display: block;
            color:white;
            line-height: 30px;
        }
        .top-list h3{
            text-align: right;
            margin-right:4px;
        }
        .top-list p{
            text-align: center;
        }

        .top-page{
            height:40px;
            margin:0 10px;
            display: flex;
            justify-content: flex-end;
            align-items: center;   
        }
        .top-page a{
            border:1px #cbcbcb solid;
            margin-left:2px;
            padding:3px 4px;
        }
        .top-page span{
            padding:3px 4px;
        }



        .theme1{
            background-image: linear-gradient(#187fe6, #32aff2);
            border:1px #2a9adc solid;
        }
        .theme2{
            background-image: linear-gradient(#f2246c, #fe5bac);
            border:1px #da2061 solid;
        }
        .theme3{
            background-image: linear-gradient(#d46300, #e5ad1c);
            border:1px #cd9818 solid;
        }
        
    </style>
</head>
<body>
    <div class="top">
        <div class="top-title">
            今日上榜
        </div>
        <div class="top-list">
            <div class="theme1">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme2">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme1">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme1">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme1">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme3">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
            <div class="theme3">
                <a href="#">
                    <h3>实时热点</h3>
                    <p>阿里第一颗芯</p>
                </a>
            </div>
        </div>
        <div class="top-page">
            <span>1</span>
            <a href="#">2</a>
            <a href="#">3</a>
        </div>
    </div>
</body>
</html>
```

## 综合案例-小米商品导航菜单

- 列自适应

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
        .nav{
            width:233px;
            height:100vh;
            background:rgba(0,0,0,0.5);
        }
        .nav>li{
            display: flex;
            justify-content: space-between;
            align-items: center;
            height:42px;
            /*因为hover不对margin染色*/
            padding:0 28px;
            cursor: pointer;
            color: white;
            position: relative;
        }
        .nav>li a{
            color:inherit;
        }
        .nav>li:hover{
            background:#ff6801;
        }
        .nav>li:hover .nav-menu{
            display: grid;
        }
        .nav-menu{
            display: none;
            position: absolute;
            left:100%;
            top:0;
            height: 460px;
            grid-template-rows: repeat(6, 1fr);
            grid-template-columns: 305px;
            grid-auto-flow: column;
            grid-auto-columns: 305px;
            background:white;
            border:1px #e1e1e1 solid;
            box-shadow: 5px 5px 10px #ccc;
            color: #36303c;
        }
        .nav-menu>li{
            display: flex;
            align-items: center;
        }
        .nav-menu>li>img{
            margin-left:26px;
            margin-right:21px;
        }
    </style>
</head>
<body>
    <ul class="nav">
        <li>
            <div>
                <a href="#">手机</a>
                <a href="#">电话卡</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
            <ul class="nav-menu">
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
            </ul>
        </li>
        <li>
            <div>
                <a href="#">笔记本</a>
                <a href="#">显示器</a>
                <a href="#">平板</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
            <ul class="nav-menu">
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
            </ul>
        </li>
        <li>
            <div>
                <a href="#">手机</a>
                <a href="#">电话卡</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
            <ul class="nav-menu">
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
                <li>
                    <img src="./phone.png" alt="">
                    <p>小米 MIX FOLD</p>
                </li>
            </ul>
        </li>
        <li>
            <div>
                <a href="#">笔记本</a>
                <a href="#">显示器</a>
                <a href="#">平板</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
        </li>
        <li>
            <div>
                <a href="#">手机</a>
                <a href="#">电话卡</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
        </li>
        <li>
            <div>
                <a href="#">笔记本</a>
                <a href="#">显示器</a>
                <a href="#">平板</a>
            </div>
            <i class="iconfont icon-right-arrow"></i>
        </li>
    </ul>
</body>
</html>
```