#lang racket
(require math/base)
 
(define listaHidrantes (list))
(define listaRadioBases (list))
(define listaQuadras (list))
(define listaPredios (list))
 
(define (escreverLista bairro lista)
    (cond
        [(empty? lista) bairro]
        [else (escreverLista (string-append bairro (first lista) "\n") (rest lista))]
    )
)
 
(define (criaCirculo id r x y corB corP)
    (string-append "c " (number->string id) " "  (number->string r) " "  (number->string x) " "  (number->string y) " " corB " " corP "\n"))
   
(define (criaHidrante id x y)
    (string-append "h " id " " (number->string x) " " (number->string y)))
 
(define (criaRadioBase id x y)
    (string-append "rb " id " " (number->string x) " " (number->string y)))
 
(define (criaPredio cep face num f p mrg)
    (string-append "prd " cep " " face " " (number->string num) " " (number->string f) " " (number->string p) " " (number->string mrg)))
 
(define (pegarFacePredio)
    (define a (random-natural 4))
    (cond
        [(equal? a 0)(string-append "N")]
        [(equal? a 1)(string-append "S")]
        [(equal? a 2)(string-append "L")]
        [(equal? a 3)(string-append "O")]
    )
)
 
(define (gerarNx numeroQuadras)
    (string-append "nx 10 " (number->string numeroQuadras) " " (number->string (* numeroQuadras 8)) " 0 " (number->string numeroQuadras) " " (number->string numeroQuadras) " 0\n"))
 
(define (colocarHidrantesERadioBaseQuadra x y w h id)
    (define inicio_x x)
    (define inicio_y y)
    (define offet_x (/ w 2))
    (define offet_y (/ h 2))
    (define colocaRadioBase 1)
    (define hidrantesERadioBase (string-append "" ) )
   
    (for ([i 3])
        (define inicio_x x)
        (for ([j 3])
            (define colocaHidrante (random-natural 2))
            (if (and (equal? i 1) (equal? j 1))( begin
                    (set! colocaHidrante 0)
                   
                    (set! colocaRadioBase (random-natural 3))
                   
                    (if (> colocaRadioBase 0)( begin
                        
                        (set! listaRadioBases (append listaRadioBases (list (criaRadioBase (string-append "rb." id) inicio_x inicio_y))))
                        ) (string-append hidrantesERadioBase "")
                    )
                   
                ) (string-append hidrantesERadioBase "")
            )( if (equal? colocaHidrante 1)( begin

                    (set! listaHidrantes (append listaHidrantes (list (criaHidrante (string-append "hid." id "." (number->string i) (number->string j) ) inicio_x inicio_y))))
                 ) (string-append hidrantesERadioBase "")
            ) (set! inicio_x (+ inicio_x offet_x))
        ) (set! inicio_y (+ inicio_y offet_y))
    )
)
 
(define (inserePredio cep w h)
    (define face (pegarFacePredio))
    (define num 1)
   
    (if (or (string=? face "N") (string=? face "S"))( begin
            (set! num (/ w 2))
        ) (set! num (/ h 2))
    )
   
    (define f (+ 40 (random-natural 21)))
    (define p (+ 40 (random-natural 21)))
    (define mrg (random-natural 21))
   
    (define predio (criaPredio cep face num f p mrg))
    (set! listaPredios (append listaPredios (list predio)))
)
 
(define (criaQuadra cep x y w h id)
    (define quadra (string-append "q " cep " " (number->string x) " " (number->string y) " " (number->string w) " " (number->string h)))
    (set! listaQuadras (append listaQuadras (list quadra)))
    (colocarHidrantesERadioBaseQuadra x y w h id)
   
    (define colocaPredio (random-natural 2))
    (if (equal? colocaPredio 1)( begin
            (inserePredio cep w h)
        ) (string-append quadra "")
    )
)
 
(define (criaBairro numQuadrasLinha numQuadrasColuna proporcao)
    (define bairro (string-append (gerarNx (* numQuadrasColuna numQuadrasLinha proporcao proporcao))))
    (define inicio_x 25)
    (define inicio_y 25)
    (define w 120)
    (define h 80)
    (define offet_x 135)
    (define offet_y 95)
   
    (for ([i (* numQuadrasLinha proporcao)])
        (set! inicio_x 25)
        (for ([j (* numQuadrasColuna proporcao)])
            (define cep (string-append "cep-" (number->string i) "-" (number->string j) ))
            (define id (string-append (number->string i) (number->string j) ))
            (criaQuadra cep inicio_x inicio_y w h id)
           
            (set! inicio_x (+ inicio_x offet_x) )
        ) (set! inicio_y (+ inicio_y offet_y) )
    )

    (set! bairro (escreverLista bairro listaQuadras))
    (set! bairro (escreverLista bairro listaHidrantes))
    (set! bairro (escreverLista bairro listaRadioBases))
    (set! bairro (escreverLista bairro listaPredios))
    
    (define circulo1 (criaCirculo 1 20 25 (+ inicio_y 60) "black" "yellow"))
    (define circulo2 (criaCirculo 2 15 inicio_x (+ inicio_y 20) "black" "yellow"))
    
    (set! bairro (string-append bairro circulo1 circulo2) )
    
    bairro
)

(define (length lst)
  (cond
    [(empty? lst)  0]
    [(cons? lst)   (+ 1 (length (rest lst)))]
    )
)
 
(define (Hidrante_getId posic)
    (list-ref (string-split (list-ref listaHidrantes posic)) 1)
)

(define (RadioBase_getId posic)
    (list-ref (string-split (list-ref listaRadioBases posic)) 1)
)

(define (Quadra_getCep posic)
    (list-ref (string-split (list-ref listaQuadras posic)) 1)
)

; A partir daqui serão definidos os comandos do qry
(define (gerar_dq comando i)
    (define posic 0)
    (define id "id")
    (define metricaL "L1")
    (define raio 150)
    (define hidrante 0)
    (define metrica 0)
    
	(if (= i 0)( begin
		comando
	    )(( lambda() (begin
    		(set! hidrante (random-natural 2))
    		(set! metrica (random-natural 2))
    		(set! raio (+ 150 (random-natural 300)) ) ; de 150 a 450
    		
    		(if (equal? metrica 1)( begin
    		        (set! metricaL "L1")
    		    ) (set! metricaL "L2")
    		)
    		
    		(if (equal? hidrante 1)( begin
    		        (set! posic (random-natural (length listaHidrantes) ))
    		        (set! id (Hidrante_getId posic))
    		    ) ( begin
    		        (set! posic (random-natural (length listaRadioBases) ))
    		        (set! id (RadioBase_getId posic))
    		    )
    		)
    		
    		(gerar_dq (string-append comando "dq " metricaL " " id " " (number->string raio) "\n" ) (- i 1)) ))
	     )
	)
)

(define (dq quantidade) ; Poderá ser aplicado a partir de um hidrante ou radioBase
   
    (define comando (string-append ""))
    (set! comando (gerar_dq comando quantidade))
    
    (define out (open-output-file (string-append "input/dq" tipo ".qry") ))
    (display comando out)
    (close-output-port out)
)

(define (del quantidade tipo) ; nome do arquivo = del{tipo}.qry
    (define comando (string-append ""))
    (define posic 0)
    (define id "id")
    
    (if (string=? tipo "Quadra")( begin
            (for ([i quantidade])
                (set! posic (random-natural (length listaQuadras) ))
                (set! id (Quadra_getCep posic))
                (set! comando (string-append comando "del " id "\n"))
            )
        )(string-append comando "")
    )
    
    (if (string=? tipo "Hidrante")( begin
            (for ([i quantidade])
                (set! posic (random-natural (length listaHidrantes) ))
                (set! id (Hidrante_getId posic))
                (set! comando (string-append comando "del " id "\n"))
            )
        )(string-append comando "")
    )
    
    (if (string=? tipo "RadioBase")( begin
            (for ([i quantidade])
                (set! posic (random-natural (length listaRadioBases) ))
                (set! id (RadioBase_getId posic))
                (set! comando (string-append comando "del " id "\n"))
            )
        )(string-append comando "")
    )
    
    (define out (open-output-file (string-append "input/del" tipo ".qry") ))
    (display comando out)
    (close-output-port out)
)

(define (trns lado) ;nome do arquivo = trns{lado}.qry
    (define comando (string-append ""))
    
    (if (string=? lado "Cima")( begin
            (set! comando (string-append comando "trns 24 24 300 200 0 -100\n"))
        )(string-append comando "")
    )
    
    (if (string=? lado "Baixo")( begin
            (set! comando (string-append comando "trns 24 24 300 200 0 100\n"))
        )(string-append comando "")
    )
    
    (if (string=? lado "Cireita")( begin
            (set! comando (string-append comando "trns 24 24 300 200 100 0\n"))
        )(string-append comando "")
    )
    
    (if (string=? lado "Esquerda")( begin
            (set! comando (string-append comando "trns 24 24 300 200 -100 0\n"))
        )(string-append comando "")
    )
    
    (define out (open-output-file (string-append "input/trns" lado ".qry") ))
    (display comando out)
    (close-output-port out)
)

(define (brl)
    (define comando (string-append ""))
    (define x (random-natural 1500))
    (define y (random-natural 1500))
    
    (set! comando (string-append comando "brl " (number->string x) " " (number->string y) "\n"))
    
    (define out (open-output-file "input/brl.qry"))
    (display comando out)
    (close-output-port out)
)

(define (fh quantidade proximidade)
    (define posic (random-natural (length listaQuadras) ))
    (define cep (Quadra_getCep posic))
    (define face (pegarFacePredio))
    (define num 1)
   
    (if (or (string=? face "N") (string=? face "S"))( begin
            (set! num (/ 120 2))
        ) (set! num (/ 80 2))
    )
    
    (define comando (string-append "fh " proximidade quantidade " " cep " " face " " (number->string num) "\n"))
    
    (define out (open-output-file "input/fh.qry"))
    (display comando out)
    (close-output-port out)
)

(define (bb sufixo cor)
    (define comando (string-append "bb " sufixo " " cor "\n"))
    (define out (open-output-file "input/bb.qry"))
    (display comando out)
    (close-output-port out)
)
 
(define bairro (criaBairro 2 2 1))
(define out (open-output-file "input/bairro.geo"))
(display bairro out)
(close-output-port out)

(dq 3)

