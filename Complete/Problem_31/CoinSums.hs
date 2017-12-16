ways :: Int -> [Int] -> Integer
ways amount [] = 0
ways 0 coins = 1
ways amount coins@(largestCoin:smallChange)
    | amount < 0 = 0
    | otherwise = ways (amount-largestCoin) coins + ways amount smallChange

ukCoins = [200, 100, 50, 20, 10, 5, 2, 1]

main = putStrLn (show (ways 200 ukCoins))
