# ksanavm
Forth Virtual Machine in plain C

## 剎那極簡虛擬機簡介

虛擬機是以軟體來模擬杜林機的技術。
Stack based virtual machine 是一種常見的虛擬機。
剎那機簡虛擬機的目標是一最簡單、最易於被理解的Stack based VM 。
對像為略懂C，或懂任何 c-like 語言的人。(如 java, c++, C#, VB, php 等)
Scripting language 的本質是一個虛擬機。
Java/ .NET / Flash Action Script/ Truetype bytecode 的本質都是stack based虛擬機
SQL, PDF 等大型軟體都有虛擬機的影子。
搞懂虛擬機將會對interpreter/compiler的本質有充份理解。
掌握虛擬機的內部工作機制，對複雜軟體系統的理解有很大的幫助。
你將有能力打造自己的scripting language 和compiler。

## Part1 : The Interpreter 直譯器 ksanavm_rev1.zip
lesson1	2007.12.20	Processing tokens 處理符素
lesson2	2007.12.20	Working with stack 堆疊
lesson3_1	2007.12.20	The execution vector 執行單元 (函式介紹)
lesson3_2	2007.12.20	The execution vector 執行單元 (追縱)

## Part2 : The Compiler 編譯器  ksanavm_rev4.zip
Lesson4	2007.12.21	Dictionary 字典
Lesson5_1	2007.12.21	Invoke a Call and Return 呼叫及返回 (介紹)
Lesson5_2	2007.12.22	Invoke a Call and Return 呼叫及返回 (追縱)
Lesson6	2007.12.22	Nested Call 巢狀呼叫
Lesson7	2007.12.24	Compiling literals 編入數值
Lesson8	2007.12.24	Colon Defination 定義新字

## Part3 : Program Structure 程序結構  ksanavm_rev5.zip
Lesson9	2008.1.21	String compiler 字串編譯
Lesson10	2008.1.21	if-then-else 改變程式流程(1)
Lesson11	2008.1.22	do-loop 改變程式流程(2)
Lesson12	2008.1.22	Variable 變數

## Part4 : Developing Application 開發應用程序  ksanavm_rev6.zip
Lesson13	2008.1.22	Localization 中文化
Lesson14	2008.1.22	Calling System API 調用系統函式
Lesson15	2008.1.23	loading external source file 載入源碼
Lesson16	2008.1.23	Recursion 遞迴呼叫：Factorial 階乘
Lesson17	2008.1.23	Array 陣列：Prime Number 質數

## Part5 : Advance Topic 進階主題
Lesson20	2011/5/25	Create Does

## 舊網頁
http://ya.ksana.tw/ksanavm/

## TODO
將powercam , wink 錄製的 swf 轉到youtube ，有成功經驗者指導。