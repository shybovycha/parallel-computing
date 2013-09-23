import Text.Printf
import Control.Parallel
import Data.List

main = do
    print c
    
    where
        a = [[1, 2, 3], [2, -1, 2]]
        b = [[3, 2, 1], [1, 3, -2], [2, 4, 2]]
        c = mmult a b
        
mmult :: Num a => [[a]] -> [[a]] -> [[a]] 
mmult a b = [ [ sum $ zipWith (*) ar bc | bc <- (transpose b) ] | ar <- a ]