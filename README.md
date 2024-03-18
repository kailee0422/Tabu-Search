
## Tabu-Search
利用Tabu Search演算法找出deception problem之最佳解(或接近最佳解) ，Tabu Search之iteration次數設定為1000，deception problem 之Bits數量設定為50。

## Algotithm 
![image](https://github.com/kailee0422/Tabu-Search/assets/71311828/93ae900a-94cf-425f-8854-708aab050365)


## deception problem f(x)=|B2D(s)-2^(n-2) |,s_i∈{0,1},n>2

## 設定參數 NUM_BITS是設定Bits數量50 MAX_TABU_LENGTH是設定Desired maximum tabu list length NUM_ITERATION是根據題目設定1000次(找到最佳解或接近最佳解) NUM_TWEAK 是設定number of tweaks desired to sample the gradient

## Tweak說明 在這邊我使用了四個調整的方法，分別是 
###### 1.隨邊更改一個位元

###### 2.更改從隨意的索引到LSB

###### 3.更改從MSB到隨意的索引

###### 4.更改將二進為數值加一
