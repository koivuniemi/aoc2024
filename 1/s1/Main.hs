import Data.List
import System.Environment
import Control.Monad (when)


totalDistance :: [[Int]] -> Int
totalDistance [l0, l1] = sum $ zipWith (\a b -> abs $ a - b) (sort l0) (sort l1)

main :: IO ()
main = do
    args <- getArgs
    when (null args)
        $ errorWithoutStackTrace "need input file"
    input <- readFile $ head args
    print $ totalDistance $ transpose $ map (map read . words) $ lines input
