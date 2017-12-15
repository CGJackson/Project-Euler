decimalDigits = [0..9]

digitsToNumbers :: (Integral a) => [a] -> a
digitsToNumbers [] = 0
digitsToNumbers (d:[]) = d
digitsToNumbers l = last l + 10 * digitsToNumbers (init l)

discrepency :: Int -> Int -> Int
discrepency n d = d * 10^n - d^5

minDiscrepency :: Int -> Int
minDiscrepency n = minimum [discrepency n d | d <- decimalDigits]

maxDiscrepency :: Int -> Int
maxDiscrepency n = maximum [discrepency n d | d <- decimalDigits]

cumulativeMinDiscrepency :: Int -> Int
cumulativeMinDiscrepency 0 = minDiscrepency 0
cumulativeMinDiscrepency n = minDiscrepency n + cumulativeMinDiscrepency (n-1)

cumulativeMaxDiscrepency :: Int -> Int
cumulativeMaxDiscrepency 0 = maxDiscrepency 0
cumulativeMaxDiscrepency n = maxDiscrepency n + cumulativeMaxDiscrepency (n-1)

listCumulativeDiscrepency :: [Int] -> Int
listCumulativeDiscrepency l = sum [discrepency i d | (i,d) <- zip [5,4..] l]

--returns a list of the numbers which equal the sum 
--of the fifth powers of their digits, starting with a given set of digits
getEqualSumOfFifthPowers :: [Int] -> [Int]
getEqualSumOfFifthPowers startingDigits
    | currentDigit == 0 = [digitsToNumbers (startingDigits ++ [d])|d <- decimalDigits, currentDisrepency d == 0]
    | otherwise = concat [getEqualSumOfFifthPowers (startingDigits ++ [d]) |
        d <- decimalDigits, 
        currentDisrepency d + cumulativeMaxDiscrepency currentDigit >= 0, 
        currentDisrepency d + cumulativeMinDiscrepency currentDigit <= 0]
    where initialDiscrepency :: Int
          initialDiscrepency = listCumulativeDiscrepency startingDigits
          currentDigit :: Int
          currentDigit = 5 - length startingDigits
          currentDisrepency :: Int -> Int
          currentDisrepency d = initialDiscrepency + discrepency currentDigit d

equalSumOfFifthPowers = concat [getEqualSumOfFifthPowers [d] | d <- [0..3]]

main = putStrLn (show (sum equalSumOfFifthPowers - 1)) 
