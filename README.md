
## Tabu-Search
利用Tabu Search演算法找出deception problem之最佳解(或接近最佳解) ，Tabu Search之iteration次數設定為1000，deception problem 之Bits數量設定為50。

## Algotithm 
![image](https://github.com/kailee0422/Tabu-Search/assets/71311828/93ae900a-94cf-425f-8854-708aab050365)


## deception problem 
Deception Problem是一個最大化問題
### 公式
f(x)=|B2D(s)-2^(n-2) |,s_i∈{0,1},n>2

### 範例
f(10100)=|(16+4)-2^(5-2) |=12

## 設定參數 
- NUM_BITS在這邊是設定Bits數量50
- MAX_TABU_LENGTH是設定Desired maximum tabu list length，在這邊是設定10
- NUM_ITERATION是根據題目設定1000次(迴圈去找到最佳解或接近最佳解)
- NUM_TWEAK 是設定number of tweaks desired to sample the gradient，在這邊是設定2

## Tweak說明 
在這邊我使用了六個調整的方法，以便照找到最好的tweak方法，其方法分別是 
#### 1.隨邊更改一個位元

#### 2.更改從隨意的索引到LSB

#### 3.更改從MSB到隨意的索引

#### 4.更改將二進位數值加一

#### 5.更改二進位數值偶數位元

#### 6.更改二進位數值奇數位元

## 結果說明 
![image](https://github.com/kailee0422/Tabu-Search/assets/71311828/bec30eee-9b01-4e03-a86f-e72b942974a6)
初值的部分，這邊是取random的值，tweak的方法如上述，經過tweak以及quality的新舊值比較，以更新tabu_list(10個為上限)並找出接近最佳解和tweak的最佳方法。
那因為我有使用rand seed的方法，以確保其隨意值不會重複
```bash
srand(time(NULL));
```
另外，我在tweak之前的隨意初始值都會不一樣，以確保其公平性。
因為初始值的不同和tweak的方式不同，所以每次執行出來的最佳解和最佳tweak的方法都會不同。
## 編譯環境
- Windows環境 Visual Studio 2022
