-- Solves Project Euler problem 76
--
-- How many possible ways can 100 be written as the sum of at least 2 positive integers
--

numberOfSums n = numberOfSums' n n

numberOfSums' :: Int -> Int -> Integer
numberOfSums' leadingTerm target
    | leadingTerm <= 1 = 0
    | target <= 1 = 0
    | leadingTerm > target = numberOfSums' target target
    | otherwise = sum $ map subSums [leadingTerm-1, leadingTerm-2..1]
        where subSums newLeadingTerm = 1 + (numberOfSums' newLeadingTerm newTarget)
                    where newTarget = target - newLeadingTerm 


main = putStrLn $ "100 can be written as a sum of 2 or more terms in " ++ (show $ numberOfSums 100) ++ " different ways."
