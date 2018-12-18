{-# OPTIONS_GHC -Wall #-}
{-# LANGUAGE MultiParamTypeClasses,
             TypeSynonymInstances, FlexibleInstances #-}

module GAS where

import ProblemState

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
    show NL = "\n"

    
data Level = Level [(Position, (Object, Object))]
    deriving (Eq, Ord)


-- Sorteaza dupa linie si apoi dupa coloana obiectele din nivel.
sortLinesAndCols :: (Ord a, Ord b) => ((a, b), c) -> ((a, b), d) -> Ordering
sortLinesAndCols a b | fst (fst a) < fst (fst b) = LT
                     | fst (fst a) > fst (fst b) = GT
                     | fst (fst a) == fst (fst b) = if snd (fst a) < snd (fst b)
                                                    then LT
                                                    else if snd (fst a) > snd (fst b)
                                                         then GT
                                                         else EQ


-- Folosita pentru a gasi coloana maxima din nivel, pentru a le putea egala.
findMaxCol :: (Ord a, Ord b) => ((a, b), c) -> ((a, b), d) -> Ordering
findMaxCol a b | snd (fst a) < snd (fst b) = LT
               | snd (fst a) > snd (fst b) = GT
               | otherwise = EQ

-- Folosita de groupBy pentru a grupa in linii obiectele.
groupInLines :: (Ord a, Ord b) => ((a, b), c) -> ((a, b), d) -> Bool
groupInLines a b = (fst (fst a)) == (fst (fst b))


-- Functie auxiliara care afiseaza obiectele.
myshow :: (a, (Object, Object)) -> [Char]
myshow (_, (Space, c)) = (show Space) ++ (show Space) ++ (show c)
myshow (_, (b, Space)) = (show b) ++ (show Space)
myshow (_, (NL, NL)) = show NL
myshow (_, (a, b)) = (show a) ++ (show b)


-- Afiseaza un nivel, aplicand, in ordine: sortare linii si coloane, adaugare newline-uri,
-- grupare dupa linie, adaugare spatii si egalare linii si adaugara bare.
instance Show Level where
        show (Level l) = concat (concat linesWithBars)
                        where sorted = (sortBy sortLinesAndCols l)
                              lines = groupBy groupInLines (reverse (foldl addNewLines [(head sorted)] (tail sorted)))
                              linesWithSpaces = (map addSpacesBetweenCols (map changeNewLineColIndex lines))
                              maxLength = snd (fst (maximumBy findMaxCol (map (maximumBy findMaxCol) linesWithFinalNL))) 
                              equalLines = if (length linesWithSpaces) == 1
                                           then linesWithSpaces
                                           else map (equalizeLinesLength maxLength) changeEmptyLineColIndex
                              linesWithBars = (map addBars ((map (map myshow) removeFinalNL)))
                              lastLine = head (reverse linesWithSpaces)
                              lastObjPos = fst (head (reverse lastLine))
                              linesWithFinalNL = (init linesWithSpaces) ++ [lastLine ++ [((fst lastObjPos, (snd lastObjPos) + 1),(NL, NL))]]
                              changeEmptyLineColIndex = map aux linesWithFinalNL
                              removeFinalNL = if (length equalLines) == 1
                                              then equalLines
                                              else (init equalLines) ++ [init (head (reverse equalLines))]

emptyLevel :: Level
emptyLevel = Level []


-- Adauga un patrat la o pozitie la care exista un obiect.
addSquareToSamePos :: Color -> Heading -> Position -> (Position, (Object, Object)) -> (Position, (Object, Object))
addSquareToSamePos c h p obj = if p == (fst obj)
                               then (p, (Square c h, (snd (snd obj))))
                               else obj


-- Adauga un patrat la nivel.
addSquare :: Color -> Heading -> Position -> Level -> Level
addSquare c h p (Level l) = if filter (\(pos, _) -> p == pos) l == []
                            then Level (l ++ [(p, (Square c h, Space))])
                            else Level (map (addSquareToSamePos c h p) l)


-- Adauga un cerc la o pozitie la care exista un obiect.
addCircleToSamePos :: Color -> Position -> (Position, (Object, Object)) -> (Position, (Object, Object))
addCircleToSamePos c p obj = if p == (fst obj)
                               then (p, ((fst (snd obj)), Circle c))
                               else obj

-- Adauga un cerc la nivel.
addCircle :: Color -> Position -> Level -> Level
addCircle c p (Level l) = if filter (\(pos, _) -> p == pos) l == []
                          then Level (l ++ [(p, (Space, Circle c))])
                          else Level (map (addCircleToSamePos c p) l)


-- Adauga o sageata la o pozitie la care exista un obiect.
addArrowToSamePos :: Heading -> Position -> (Position, (Object, Object)) -> (Position, (Object, Object))
addArrowToSamePos h p obj = if p == (fst obj)
                             then (p, ((fst (snd obj)), Arrow h))
                             else obj

-- Adauga o sageata la nivel.
addArrow :: Heading -> Position -> Level -> Level
addArrow h p (Level l) = if filter (\(pos, _) -> p == pos) l == []
                         then Level (l ++ [(p, (Space, Arrow h))])
                         else Level (map (addArrowToSamePos h p) l)


-- Un obiect newline.
newLineObj :: (Position, (Object, Object))
newLineObj = ((-1, -1), (NL, NL))

-- Schimba indexul obiectelor dintr-o linie. 
changeLineIndex :: Int -> [(Position, a)] -> [(Position, a)] 
changeLineIndex lineIndex l = zipWith (\(pos, objs) line -> ((line, snd pos), objs)) l [lineIndex .. lineIndex + ((length l) - 1)]


-- Adauga newlines la fiecare linie si la liniile care lipsesc.
addNewLines :: [(Position, (Object, Object))] -> (Position, (Object, Object)) -> [(Position, (Object, Object))]
addNewLines l obj = [obj] ++ newlines ++ l
                    where newlines = reverse (changeLineIndex (fst (fst (head l))) (replicate ((fst (fst obj)) - (fst (fst (head l)))) newLineObj))


-- Delimiteaza coloanele.
delimCols :: [[Char]] -> [[Char]]
delimCols l = intersperse "|" l


-- Adauga spatii intre coloane.
addSpacesBetweenColsAux :: [(Position, (Object, Object))] -> (Position, (Object, Object)) -> [(Position, (Object, Object))]
addSpacesBetweenColsAux l obj = [obj] ++ spaces ++ l
                                where spaces = (replicate ((snd (fst obj)) - (snd (fst (head l))) - 1) newSpaceObj)
                                      newSpaceObj = ((fst (fst obj), (snd (fst (head l))) + 1), (Space, Space)) 

-- Adauga spatii intre coloane, folosind foldl cu functia precedenta.
addSpacesBetweenCols :: [(Position, (Object, Object))] -> [(Position, (Object, Object))]
addSpacesBetweenCols line = reverse (foldl addSpacesBetweenColsAux [(head line)] (tail line))


-- Schimba indexul coloanelor, astfel, incat sa nu fie diferente > 1 intre ele.
changeNewLineColIndex :: (Eq b, Num b) => [((a, b), c)] -> [((a, b), c)]
changeNewLineColIndex line = if snd (fst lastElem) == -1 && (length line) > 1
                             then (init line) ++ [((fst (fst lastElem), (snd (fst anteLastElem)) + 1), snd lastElem)]
                             else line
                             where lastElem = head (reverse line)
                                   anteLastElem = head (reverse (init line))

-- Face liniile de dimensiuni egale, adaugand spatii inainte si dupa obiecte.
equalizeLinesLength :: Int -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
equalizeLinesLength max line = if snd (head line) == (NL, NL)
                              then (replicate (max - aux) ((-1, -1), (Space, Space))) ++ line
                              else (replicate (snd (fst (head line))) ((-1, -1), (Space, Space))) ++
                                   (init line) ++
                                   (replicate (max - aux) ((-1, -1), (Space, Space))) ++
                                   [(head (reverse line))]
                              where aux = snd (fst (head ((reverse line))))


-- Elimina ultimul spatiu din nivel.
removeLastSpaces :: [[(Position, (Object, Object))]] -> [[(Position, (Object, Object))]]
removeLastSpaces l = (init l) ++ [(init lastLine)]
                     where lastLine = head (reverse l)

-- Face indexul coloanei unui obiect newline 0, in caz ca e un rand liber (e doar newline pe rand), 
-- altfel, ar fi fost -1 si s-ar fi adaugat un spatiu in plus (de la 0 la -1).
aux :: [(Position, (Object, Object))] -> [(Position, (Object, Object))]
aux line = if (snd firstElem) == (NL, NL)
           then [((fst (fst firstElem), 0),snd firstElem)]
           else line
           where firstElem = head line

-- Adauga bare intre coloane.
addBars :: [[Char]] -> [[Char]]
addBars line = if lastElem /= "\n"
               then (intersperse "|" line)
               else (intersperse "|" (init line)) ++ [head (reverse line)]
               where lastElem = head (reverse line)
              

-- Returneaza urmatoarea pozitie, la care trebuie sa se mute patratul.
getNextPos :: Position -> Object -> Position
getNextPos pos (Square _ h) | h == North = ((fst pos) - 1, snd pos)
                            | h == South = ((fst pos) + 1, snd pos)
                            | h == East = (fst pos, (snd pos) + 1)
                            | h == West = (fst pos, (snd pos) - 1)

-- Modifica pozitia unui patrat.
changeSquarePos :: Position -> Position -> (Position, (Object, Object)) -> (Position, (Object, Object))
changeSquarePos pos1 nextPos (pos2, (Square c h, Space)) | pos1 == pos2 = (nextPos, (Square c h, Space))
                                                         | otherwise = (pos2, (Square c h, Space))
changeSquarePos _ _ (pos2, (Space, Circle c)) = (pos2, (Space, Circle c))
changeSquarePos _ _ (pos2, (Space, Arrow h)) = (pos2, (Space, Arrow h))

-- Modifica orientarea unui patrat.
changeSquareHeading :: Object -> Object -> Object
changeSquareHeading (Square c _) (Arrow h2) = (Square c h2)


-- Schimba headingul unui patrat cu al altui patrat, in cazul in care un patrat muta altul.
changeSquareHeadingTemp :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> (Position, (Object, Object))
changeSquareHeadingTemp (_, (Square _ h1, _)) (pos2, (Square c2 _, obj2)) = (pos2, (Square c2 h1, obj2))  

-- Sterge un element din lista.
delElem :: (Eq a, Foldable t) => a -> t a -> [a]
delElem el l = foldl (\xs x -> if x == el then xs else xs ++ [x]) [] l


-- Muta un patrat peste un cerc.
squareToCircle :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
squareToCircle square circle l = map (\obj -> if ((fst square == fst obj) && (fst (snd obj) /= Space)) then newObj else obj) (delElem circle l)
                                 where newObj = (fst circle, (fst (snd square), snd (snd circle)))

-- Muta un patrat peste o sageata.
squareToArrow :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
squareToArrow square arrow l = map (\obj -> if ((fst square == fst obj) && (fst (snd obj) /= Space)) then newObj else obj) (delElem arrow l)
                               where newObj = (fst arrow, (changeSquareHeading (fst (snd square)) (snd (snd arrow)), snd (snd arrow)))


-- Verifica daca sunt aceleasi patrate, inainte ca headingul sa se fi schimbat.
checkIfEqual :: Object -> Object -> Bool
checkIfEqual (Square c1 h1) (Square c2 _) = (Square c1 h1) == (Square c2 h1)
checkIfEqual (Square _ _) _ = False
checkIfEqual _ _ = False


-- Gaseste unde se afla un patrat, inainte sa fie mutat si sa-i fie schimbata directia.
findPrevSquare :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> (Position, (Object, Object)) -> Bool
findPrevSquare _ sq2 obj = ((fst sq2) == ((fst (fst obj)) - 1, (snd (fst obj))) ||
                             (fst sq2) == ((fst (fst obj)) + 1, (snd (fst obj))) ||
                             (fst sq2) == ((fst (fst obj)), (snd (fst obj)) - 1) ||
                             (fst sq2) == ((fst (fst obj)), (snd (fst obj)) + 1)) && (checkIfEqual (fst (snd sq2)) (fst (snd obj)))

-- Extrage lista dintr-un obiect nivel.
getLevelList :: Level -> [(Position, (Object, Object))]
getLevelList (Level l) = l


-- Muta un patrat peste un patrat. newLevel este nivelul cu patratul urmator mutat.
squareToSquare :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
squareToSquare sq1 sq2 l = map (\obj -> if ((fst sq1 == fst obj) && (fst (snd obj) /= Space)) then newObj else obj) newLevel
                           where newObj = (fst sq2, (fst (snd sq1), Space))
                                 newLevel = map (\obj -> if (findPrevSquare sq1 sq2 obj) then (changeSquareHeadingTemp sq2 obj) else obj)
                                            (getLevelList (move (fst sq2) (Level tempHeadChanged)))
                                 tempHeadChanged = (map (\obj -> if sq2 == obj then (changeSquareHeadingTemp sq1 sq2) else obj) l)

-- Verifica ce element se afla pe pozitia pe care trebuie sa se mute obiectul.
checkNextPosElem :: (Position, (Object, Object)) -> (Position, (Object, Object)) -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
checkNextPosElem square (pos, (Space, Circle c)) l = squareToCircle square (pos, (Space, Circle c)) l
checkNextPosElem square (pos, (Space, Arrow h)) l = squareToArrow square (pos, (Space, Arrow h)) l
checkNextPosElem square (pos, (Square c h, Space)) l = squareToSquare square (pos, (Square c h, Space)) l
checkNextPosElem square (pos, (Square c1 h, Circle c2)) l = squareToSquare square (pos, (Square c1 h, Circle c2)) l
checkNextPosElem square (pos, (Square c h1, Arrow h2)) l = squareToSquare square (pos, (Square c h1, Arrow h2)) l
checkNextPosElem _ _ l = l

-- Imparte o locatie ce contine doua obiecte, in doua obiecte diferite. 
splitAux :: (Position, (Object, Object)) -> [(Position, (Object, Object))] -> (Position, (Object, Object)) -> [(Position, (Object, Object))]
splitAux (_, (Square _ _, Space)) l el = l ++ [el]
splitAux (pos, (Square c1 h, Circle c2)) l el = if el == (pos, (Square c1 h, Circle c2))
                                                then l ++ [(pos, (Square c1 h, Space)), (pos, (Space, Circle c2))]
                                                else l ++ [el]
splitAux (pos, (Square c h1, Arrow h2)) l el = if el == (pos, (Square c h1, Arrow h2))
                                               then l ++ [(pos, (Square c h1, Space)), (pos, (Space, Arrow h2))]
                                               else l ++ [el]
splitAux _ l _ = l

-- Aplica splitAux pe nivel.
split :: (Position, (Object, Object)) -> [(Position, (Object, Object))] -> [(Position, (Object, Object))]
split square l = foldl (splitAux square) [] l


-- Mută pătratul de la poziția precizată din nivel. Dacă la poziția respectivă
-- nu se găsește un pătrat, întoarce direct parametrul.
move :: Position  -- Poziția
     -> Level     -- Nivelul inițial
     -> Level     -- Nivelul final
move p (Level l) = if getObjAtPos == []
                   then (Level l)
                   else if getSquareAtPos == []
                        then (Level l)
                        else if nextPosElem == []    -- daca nu exista niciun obiect la urmatoarea pozitie
                             then Level (map (changeSquarePos (fst theSquare) nextPos) (split theSquare l))
                             else Level (checkNextPosElem theSquare (head nextPosElem) (split theSquare l))
                   where getObjAtPos = (filter (\obj -> (fst obj) == p) l)
                         getSquareAtPos = filter (\obj -> fst (snd obj) /= Space) getObjAtPos
                         theSquare = head getSquareAtPos
                         nextPos = getNextPos (fst theSquare) (fst (snd theSquare))
                         nextPosElem = (filter (\obj -> (fst obj) == nextPos) l)
           

{-
    *** TODO ***

    Instanțiați clasa `ProblemState` pentru jocul nostru.
-}
instance ProblemState Level Position where
    successors = undefined

    isGoal = undefined

    -- Doar petru BONUS
    -- heuristic =
