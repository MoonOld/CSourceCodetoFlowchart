==My internship in bingyan again. Hope for "GL&HF"==



## 十月二日

* 复习Git，创建开发环境并将其push到github上
* 去图书馆借来龙书和两本实现教程用于学习阅读
* 在github上找到c4（c in 4 functions）项目，及一个模仿c4写编译器的博客教程，预计将作为主要参考资料。
* 根据博客写好词法分析函数next（）的框架
* 复习c语言词法准备开始莽
* 参考学习了《编译系统原理》中的c语言词法分析状态转换图。不得不说这本书是真的细致，不愧上千页的体量。
* 晚上完成了大多数符号的词法分析，还需第二天进一步的努力



## 十月三日

* 基本把词法分析器写好了，但是输入方式还没有转化好，需要进一步工作，宏也没有处理
* 阅读学长提供的，以及自己查找的资料，整理下一步praser需要做的事情。

* 重新设计了一下源代码到语法树的路线



## 十月四日

* 重新调整了一下思路，没有实际代码贡献
* 思考中给忘了push日报....哭哭啼啼



## 十月五日

* 词法分析器重构完成
* 构建了测试函数和文件，但是文件始终有打不开的问题，正在debug
* 使用了绝对路径，并修改读取模式后确认词法分析器基本正确完成。
* 进一步构建文法，逐步设计AST



## 十月六日

由于腿伤，进度迟缓。

* 完成文法设计
* 手写经历了一遍AST生成过程
* 基本完成函数定义部分语法分析



## 十月七日

去医院做了检查和治疗。。。进度迟缓



* 完成函数定义部分语法分析
* 完成变量分析
* 有几个语法要求还未实现（如宏定义、声明修饰符、不支持初始化等
* 词法分析需要进一步跟进，有几个token没有标示好



## 十月八日

* 在github上找到c语言读写json格式的库，准备用轮子了
* 正在构建需要输出的json（各个流程框）
* 思维有点宕机了

* 学习了一下graphviz in python，准备先顺序输出ast，再由python调用输出的json信息进行连线
* 其中json信息就只用包括label和shape
* 输出AST应该也会采用自顶向下的方法