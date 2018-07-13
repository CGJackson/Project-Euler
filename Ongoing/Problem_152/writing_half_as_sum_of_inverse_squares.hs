inverseSquare :: Fractional a => Int -> a
inverseSquare n = 1/(fromIntegral (n*n))

sumInverseSquares :: Fractional a => [Int] -> a
sumInverseSquares = sum . map inverseSquare 

getSumInverseSquares :: (Fractional a , Ord a) => a -> Int -> [[Int]]
getSumInverseSquares target limit = getSumInverseSquares' target (sumInverseSquares intRange) intRange
    where intRange = [2..limit]
          getSumInverseSquares' :: (Fractional a, Ord a) => a -> a -> [Int] -> [[Int]]
          getSumInverseSquares' target remaining (n:l)
                | target > remaining = []
                | target == inverseSquare n = [n]:sumsWithoutN
                | otherwise = (sumsWithN ++ sumsWithoutN)
                    where sumsWithN 
                                | inverseSquare n > target = []
                                | otherwise = map (n:) $ getSumInverseSquares' (target-inverseSquare n) (remaining-inverseSquare n) l
                          sumsWithoutN = getSumInverseSquares' target (remaining-inverseSquare n) l
          getSumInverseSquares' _ _ [] = []
