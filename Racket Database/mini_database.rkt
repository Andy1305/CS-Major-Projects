(define NULL 'null)

;====================================
;=            Cerința 1             =
;= Definirea elementelor de control =
;=          20 de puncte            =
;====================================

;= Funcțiile de acces

(
 define init-database
  (
   λ () null
  )
)

(
 define create-table
  (
   λ (table columns-name)
    (
     cons table (cons columns-name null)
    )
  )
)

(
 define get-name
  (
   λ (table)
    (
     car table
    )
  )
)

(
 define get-columns
  (
   λ (table)
    (
     cadr table
    )
  )
)

(
 define get-tables
  (
   λ (db) db
  )
)

(
 define get-table
  (
   λ (db table-name)
     (
      car (filter (λ (table) (equal? table-name (car table))) db)
     )
  )
)

(
 define add-table
  (
   λ (db table)
     (
      reverse (cons table (reverse db))
     )
  )
)

(define remove-table
  (
   λ (db table-name)
    (
     filter (λ (table) (not (equal? table-name (car table)))) db
    )
  )
)

;= Pentru testare, va trebui să definiți o bază de date (având identificatorul db) cu următoarele tabele

;============================================================================================
;=                         Tabela Studenți                                                   =
;= +----------------+-----------+---------+-------+-------+                                  =
;= | Număr matricol |   Nume    | Prenume | Grupă | Medie |                                  =
;= +----------------+-----------+---------+-------+-------+                                  =
;= |            123 | Ionescu   | Gigel   | 321CA |  9.82 |                                  =
;= |            124 | Popescu   | Maria   | 321CB |  9.91 |                                  =
;= |            125 | Popa      | Ionel   | 321CC |  9.99 |                                  =
;= |            126 | Georgescu | Ioana   | 321CD |  9.87 |                                  =
;= +----------------+-----------+---------+-------+-------+                                  =
;=                                                                                           =
;=                                         Tabela Cursuri                                    =
;= +------+----------+-----------------------------------+---------------+------------+      =
;= | Anul | Semestru |            Disciplină             | Număr credite | Număr teme |      =
;= +------+----------+-----------------------------------+---------------+------------+      =
;= | I    | I        | Programarea calculatoarelor       |             5 |          2 |      =
;= | II   | II       | Paradigme de programare           |             6 |          3 |      =
;= | III  | I        | Algoritmi paraleli și distribuiți |             5 |          3 |      =
;= | IV   | I        | Inteligență artificială           |             6 |          3 |      =
;= | I    | II       | Structuri de date                 |             5 |          3 |      =
;= | III  | II       | Baze de date                      |             5 |          0 |      =
;= +------+----------+-----------------------------------+---------------+------------+      =
;============================================================================================
(define db
  '(
    (
      "Studenți" ("Număr matricol" "Nume" "Prenume" "Grupă" "Medie")
                 (("Număr matricol" . 123)  ("Nume" . "Ionescu")    ("Prenume" . "Gigel")  ("Grupă" . "321CA")  ("Medie" . 9.82))
                 (("Număr matricol" . 124)  ("Nume" . "Popescu")    ("Prenume" . "Maria")  ("Grupă" . "321CB")  ("Medie" . 9.91))
                 (("Număr matricol" . 125)  ("Nume" . "Popa")       ("Prenume" . "Ionel")  ("Grupă" . "321CC")  ("Medie" . 9.99))
                 (("Număr matricol" . 126)  ("Nume" . "Georgescu")  ("Prenume" . "Ioana")  ("Grupă" . "321CD")  ("Medie" . 9.87))
    )
    (
      "Cursuri" ("Anul" "Semestru" "Disciplină" "Număr credite" "Număr teme")
                (("Anul" . "I")    ("Semestru" . "I")   ("Disciplină" . "Programarea calculatoarelor")        ("Număr credite" . 5)  ("Număr teme" . 2))
                (("Anul" . "II")   ("Semestru" . "II")  ("Disciplină" . "Paradigme de programare")            ("Număr credite" . 6)  ("Număr teme" . 3))
                (("Anul" . "III")  ("Semestru" . "I")   ("Disciplină" . "Algoritmi paraleli și distribuiți")  ("Număr credite" . 5)  ("Număr teme" . 3))
                (("Anul" . "IV")   ("Semestru" . "I")   ("Disciplină" . "Inteligență artificială")            ("Număr credite" . 6)  ("Număr teme" . 3))
                (("Anul" . "I")    ("Semestru" . "II")  ("Disciplină" . "Structuri de date")                  ("Număr credite" . 5)  ("Număr teme" . 3))
                (("Anul" . "III")  ("Semestru" . "II")  ("Disciplină" . "Baze de date")                       ("Număr credite" . 5)  ("Număr teme" . 0))
     )
   )
)

;====================================
;=            Cerința 2             =
;=         Operația insert          =
;=            10 puncte             =
;====================================

(define (filter-null-lists list) (if (null? list) #f #t))


(
 define (get-pair col record)
  (
   if (null? record)
      (cons col NULL)
      (
       if (equal? col (caar record))
          (car record)
          (get-pair col (cdr record))
      )
  )
)

;; Ia lista de colone si ce trebuie sa insereze, si returneaza lista ok cu ce trebuie sa insereze.
(
 define (entry cols record)
  (
   if (null? cols)
       null
      (cons (get-pair (car cols) record) (entry (cdr cols) record))
  )
)


(
 define (insert-in-table table-name record)
  (
   λ (table)
    (
     if (equal? table-name (car table))
        (reverse (cons (entry (cadr table) record) (reverse table)))
        table
    )
  )
)

(
 define insert
  (
   λ (db table-name record)
    (
     map (insert-in-table table-name record) db
    )
  )
)



;====================================
;=            Cerința 3 a)          =
;=     Operația simple-select       =
;=             10 puncte            =
;====================================

(
 define (select-entries-aux col line)
  (
      map (λ (pair) (cdr pair)) (filter (λ (entry) (equal? col (car entry))) line)
  )
)

(
 define (select-entries col lines)
  (
   if (null? lines)
      null
      (append (select-entries-aux col (car lines)) (select-entries col (cdr lines)))
  )
)

(
 define (select-cols cols lines)
  (
   if (null? cols)
      null
      (cons (select-entries (car cols) lines) (select-cols (cdr cols) lines))
  )
)


(
 define simple-select
  (
   λ (db table-name columns)
    (
     filter filter-null-lists (select-cols columns (cddr (get-table db table-name)))
    )
  )
)

;====================================
;=            Cerința 3 b)          =
;=           Operația select        =
;=            30 de puncte          =
;====================================
(
 define (parse-columns cols)
  (
   if (null? cols)
      null
      (
       if (pair? (car cols))
          (cons (cdar cols) (parse-columns (cdr cols)))
          (cons (car cols) (parse-columns (cdr cols)))
      )
  )
)


;; Cauta un element intr-o linie (ex. matematica). Daca il gaseste, intoarce linia, altfel '().
(
 define (get-lines-aux col line)
  (
   if (null? line)
      #f
      (
       if (equal? col (cdar line))
          #t
          (get-lines-aux col (cdr line))
      )
  )
)

;; Cauta elementul in toate liniile, prin functia get-lines-aux. Intoarce toate liniile in care s-a gasit elementul. Contine si liste vide care trebuie eliminate.
(
 define (get-lines col all-lines)
  (
   if (null? all-lines)
      null
      (
       if (equal? (get-lines-aux col (car all-lines)) #t)
          (cons (car all-lines) (get-lines col (cdr all-lines)))
          (get-lines col (cdr all-lines))
      )
  )
)

(
 define (check-each-cond line cond)
  (
   (car cond) (get-col-value (cadr cond) line) (caddr cond)
  )
)


(
 define (check-conds-aux line conds col-name)
 (
    if (null? conds)
       col-name
       (
        if (equal? (check-each-cond line (car conds)) #t)
           (check-conds-aux line (cdr conds) col-name)
           null
       )
  )
)


(
 define (check-conds lines conds col-name)
  (
   if (null? lines)
      null
      (
       if (null? (check-conds-aux (car lines) conds col-name))
          (check-conds (cdr lines) conds col-name)
          (cons (check-conds-aux (car lines) conds col-name) (check-conds (cdr lines) conds col-name))
      )
  )
)

(
 define (get-col-value col-name line)
  (
   cdar (filter (λ (pair) (equal? col-name (car pair))) line)
  )
)

(
 define (apply-each-cond line cond)
  (
    if (equal? (get-col-value (cadr cond) line) NULL)
       #f
       ((car cond) (get-col-value (cadr cond) line) (caddr cond))
  )
)

(
 define (apply-conds-aux line conds)
  (
   if (null? conds)
      line
      (
       if (equal? (apply-each-cond line (car conds)) #t)
          (apply-conds-aux line (cdr conds))
          null
      )
  )
)

(
 define (apply-conditions lines conds)
  (
   if (null? lines)
      null
      (cons (apply-conds-aux (car lines) conds) (apply-conditions (cdr lines) conds))
  )
)

(
 define (parse-ops cols)
  (
   if (null? cols)
      null
      (
       if (pair? (car cols))
          (cons (caar cols) (parse-ops (cdr cols)))
          (cons NULL (parse-ops (cdr cols)))
      )
  )
)

(
 define (apply-each-op op col)
  (
   cond
    ((equal? op 'min)       (apply min col))
    ((equal? op 'max)       (apply max col))
    ((equal? op 'count)     (length (remove-duplicates col)))
    ((equal? op 'sum)       (foldl + 0 col))
    ((equal? op 'avg)       (/ (foldl + 0 col) (length col)))
    ((equal? op 'sort-asc)  (sort col <))
    ((equal? op 'sort-desc) (sort col >))
    (else col)
  )
)

(
 define (apply-ops ops cols)
  (
   if (null? ops)
      null
      (cons (apply-each-op (car ops) (car cols)) (apply-ops (cdr ops) (cdr cols)))
  )
)

(define select
  (
   λ (db table-name columns conditions)
    (
     filter filter-null-lists (apply-ops (parse-ops columns) (select-cols (parse-columns columns) (filter filter-null-lists (apply-conditions (cddr (get-table db table-name)) conditions))))
    )
  )
)

;====================================
;=             Cerința 4            =
;=           Operația update        =
;=            20 de puncte          =
;====================================

(
 define (update-each-value line value)
  (
   map (λ (pair) (if (equal? (car pair) (car value)) (cons (car pair) (cdr value)) pair)) line
  )
)

(
 define (update-line line values)
  (
   let loop ((line line) (values values))
    (
     if (null? values)
        line
        (loop (update-each-value line (car values)) (cdr values))
    )
  )
)

(
 define (update-apply-conds line conds values)
  (
   if (null? conds)
      (update-line line values)
      (
       if (equal? (apply-each-cond line (car conds)) #t)
          (update-apply-conds line (cdr conds) values)
          line
      )
  )
)

(
 define (update-lines-aux lines conds values)
  (
   if (null? lines)
      null
      (cons (update-apply-conds (car lines) conds values) (update-lines-aux (cdr lines) conds values))
  )
)

(
 define (update-aux table values conds)
  (
   cons (car table) (cons (cadr table) (update-lines-aux (cddr table) conds values))
  )
)

(
 define update
  (
   λ (db table-name values conditions)
    (
     if (null? db)
        db
        (
         if (equal? table-name (caar db))
            (cons (update-aux (car db) values conditions) (cdr db)) 
            (cons (car db) (update (cdr db) table-name values conditions))
        )
    )
  )
)

;====================================
;=             Cerința 5            =
;=           Operația remove        =
;=              10 puncte           =
;====================================

(
 define (delete-all-lines table)
 (
  cons (car table) (cons (cadr table) null)
 )
)

(
 define (delete-lines-aux lines conds)
 (
  if (null? lines)
     null
     (
      if (equal? (check-conds-aux (car lines) conds "delete") "delete")
         (delete-lines-aux (cdr lines) conds)
         (cons (car lines) (delete-lines-aux (cdr lines) conds))
     )
 )
)

(
 define (delete-lines table conds)
  (
   append (delete-all-lines table) (delete-lines-aux (cddr table) conds)
  )
)

;; Returneaza tabelul cu liniile sterse.
(
 define (delete-aux table conds)
  (
   if (null? conds)
      (delete-all-lines table)
      (delete-lines table conds)
  )
)

(
 define delete
  (
   λ (db table-name conditions)
    (
     if (null? db)
        null
        (
         if (equal? (caar db) table-name)
            (cons (delete-aux (car db) conditions) (cdr db))
            (cons (car db) (delete (cdr db) table-name conditions))
        )
    )
  )
)

;====================================
;=               Bonus              =
;=            Natural Join          =
;=            20 de puncte          =
;====================================
(
 define (filter-nulls cols)
  (
   if (null? cols)
      null
      (cons (filter (λ (x) (if (equal? x NULL) #f #t)) (car cols)) (cdr cols))
  )
)

(define natural-join
  (
   λ (db tables columns conditions)
    (
     if (null? tables)
        null
        (append (filter-nulls (select db (car tables) columns conditions)) (natural-join db (cdr tables) columns conditions))
    )
  )
)
