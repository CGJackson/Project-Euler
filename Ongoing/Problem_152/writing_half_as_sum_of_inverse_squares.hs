inverseSquare :: Int -> Fractional
inverseSquare n = 1/(n*n)

sumInverseSquares [Int] -> Fractional
sumInverseSquares = sum map inverseSquare 

getSumInverseSquares :: Fractional -> Int -> [[Int]]
getSumInverseSquares target limit = getSumInverseSquares' target (sumInverseSquares intRange) intRange
    where intRange = [2..limit]
          getSumInverseSquares' :: Fractional -> Fractional -> [Int] -> [[Int]]
          getSumInverseSquares' target remaining n:l
                | target > remaining = []
                | target == inverseSquare n = [n]:sumsWithoutN
                | otherwise = (sumsWithN ++ sumsWithoutN)
                    where sumsWithN 
                                | inverseSquare n > target = []
                                | otherwise = map (n:) getSumInverseSquares' (target-inverseSquare n) (remaining-inverseSquare n) l
                          sumsWithoutN = getSumInverseSquares' target (remaining-inverseSquare n) l
