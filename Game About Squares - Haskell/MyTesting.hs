import qualified Data.Map.Strict as M
import qualified Data.Char
import Data.List


type Position = (Int, Int)

data Color = Red | Blue | Gray
    deriving (Eq, Ord, Show)

data Heading = North | South | East | West
    deriving (Eq, Ord)

instance Show Heading where
    show North = "^"
    show South = "v"
    show East  = ">"
    show West  = "<"
    

data Object = Square Color Heading | Circle Color | Arrow Heading | Space | NL
    deriving (Eq, Ord)    

instance Show Object where
    show (Square c h) = [(head (show c))] ++ (show h)
    show (Circle c) = [Data.Char.toLower (head (show c))]
    show (Arrow h) = show h
    show Space = " "
    show NL = "AAA"
    
data Level = Level [(Position, (Object, Object))]
    deriving (Eq, Ord)
    
-- Sorteaza dupa linie si apoi dupa coloana
sortLines a b | fst (fst a) < fst (fst b) = LT
              | fst (fst a) > fst (fst b) = GT
              | fst (fst a) == fst (fst b) = if snd (fst a) < snd (fst b)
                                             then LT
                                             else if snd (fst a) > snd (fst b)
                                                  then GT
                                                  else EQ
           

groupInLines a b = (fst (fst a)) == (fst (fst b))


myshow (a, (Space, c)) = (show Space) ++ (show Space) ++ (show c)
myshow (a, (b, Space)) = (show b) ++ (show Space)
myshow (a, (NL, NL)) = show NL


instance Show Level where
        show (Level l) = undefined

addSquare :: Color -> Heading -> Position -> Level -> Level
addSquare c h p (Level l) = Level (l ++ [(p, (Square c h, Space))])

addCircle :: Color -> Position -> Level -> Level
addCircle c p (Level l) = Level (l ++ [(p, (Space, Circle c))])

addArrow :: Heading -> Position -> Level -> Level
addArrow h p (Level l) = Level (l ++ [(p, (Space, Arrow h))])

newLineObj = ((-1, -1), (NL, NL))

addNewLines l obj = [obj] ++ (replicate ((fst (fst obj)) - (fst (fst (head l)))) newLineObj) ++ l
delimCols l = if (filter (\str -> str == "AAA") l) == []
              then intersperse "|" l
              else l

test (Level l) = map delimCols (map (map myshow) (groupBy groupInLines (reverse (foldl addNewLines [(head lines)] (tail lines)))))
                 where lines = (sortBy sortLines l)





level = Level [((2, 0), (Space, Circle Red)), ((0, 0), (Square Red South, Space))]
