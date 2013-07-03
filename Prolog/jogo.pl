% Autor: Luis Oliveira e Ricardo Leal
% Data: 29-09-2011

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%                 Sockets                   %%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

:-use_module(library(sockets)).	
:-use_module(library(random)).

port(60070).

server:-
        port(Port),
        socket_server_open(Port, Socket),
        socket_server_accept(Socket, _Client, Stream, [type(text)]),
        write('Accepted connection'), nl,
        serverLoop(Stream),
        socket_server_close(Socket).
        
% wait for commands
serverLoop(Stream) :-
        repeat,
        read(Stream, ClientMsg),
        write('Received: '), write(ClientMsg), nl,
        parse_input(ClientMsg, MyReply),
        format(Stream, '~q.~n', [MyReply]),
        write('Wrote: '), write(MyReply), nl,
        flush_output(Stream),
        (ClientMsg == quit; ClientMsg == end_of_file), !.

parse_input(initialBoard, Answer) :-
        board(Answer).
        
parse_input(quit, ok-bye) :- !.	
                
parse_input(singleMov(Xi,Yi,Xf,Yf,Board), Answer) :- singleMov(Xi,Yi,Xf,Yf,Board,Answer).

parse_input(combMov(Xi,Yi,Xf,Yf,Board),Answer) :- combMov(Xi,Yi,Xf,Yf,Board,Answer).

parse_input(changePec(Xf,Yf,Board),Answer) :- changePec(Xf,Yf,Board,Answer).

parse_input(validMov(Xi,Yi,Xf,Yf,Board),Answer) :- validMov(Xi,Yi,Xf,Yf,Board,Answer).

parse_input(dist(Xi,Yi,Xf,Yf), Answer) :- dist(Xi,Yi,Xf,Yf,Answer).

parse_input(afterPass(Board,Player), Answer) :- afterPass(Board,Answer,Player).

parse_input(aI(Board,Piece), Answer) :- aI(Board,Answer,Piece,0).




%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%             Tratamento do tabuleiro                    %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


board([[1,0,0,0,0,0,0,2],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[0,0,0,0,0,0,0,0],
[2,0,0,0,0,0,0,1]]).


convert(0, ' ').
convert(1, 'O').
convert(2, 'X').

drawboard(top) :- write('     1     2     3     4     5     6     7     8'), nl,
                  write('   _____ _____ _____ _____ _____ _____ _____ _____'),
                  nl.

drawboard(base) :- write('  |_____|_____|_____|_____|_____|_____|_____|_____|'),nl.

drawboard(blank):- write('  |     |     |     |     |     |     |     |     |'), nl.

drawpiece(X) :- write('  '),
                convert(X, T),
                write(T),
                write('  |').


showboard([X|Rest]) :- drawboard(top),
                       show([X|Rest], 1),
                       nl.

show([],_).
show([L|Rest], N) :- drawboard(blank),
                     write(N),
                     write(' |'),
                     showline(L),
                     nl,
                     drawboard(base),
                     N2 is N + 1,
                     show(Rest, N2).

showline([]).
showline([Elem|Rest]) :- drawpiece(Elem),
                         showline(Rest).
%imprime o tabuleiro
board :- board(T), showboard(T).

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%                Logica de jogo                          %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


%Retorna a peça que se encontra na Coordenada X,Y do tabuleiro
findPiece(B, X, Y, Piece):- findPiece(B, X, Y, 1, 1, Piece).

findPiece([H|_], X, Y, IteratorX, Y, Piece):- findPieceAtLine(H, X, IteratorX, Piece).
findPiece([_|T], X, Y, IteratorX, IteratorY, Piece):- ItY is IteratorY + 1,
                                                      findPiece(T, X, Y, IteratorX, ItY, Piece).
findPieceAtLine([H|_], X, X, H).
findPieceAtLine([_|T], X, IteratorX, Piece):- ItX is IteratorX+1,
                                              findPieceAtLine(T, X, ItX, Piece).

%Substitui uma peca no tabuleiro
substPiece(X, Y, PNova, Tab, TabNovo) :- substPiece(X, Y, 1, PNova, Tab, TabNovo).
substPiece(_, _, _, _, [], []).
substPiece(X, Y, Y, PecaNova, [L | Resto], [LNova | Resto2]) :- substLinePiece(X, 1, PecaNova, L, LNova),
                                                                ItY1 is Y + 1,
                                                                substPiece(X, Y, ItY1, PecaNova, Resto, Resto2).

substPiece(X, Y, ItY, PecaNova, [L | Resto], [L | Resto2]) :- ItY \= Y,
                                                              ItY1 is ItY + 1,
                                                              substPiece(X, Y, ItY1, PecaNova, Resto, Resto2).

substLinePiece(_, _, _, [], []).
substLinePiece(X, X, PecaNova, [_ | Resto], [PecaNova | Resto2]) :- ItX1 is X + 1,
                                                                    substLinePiece(X, ItX1, PecaNova, Resto, Resto2).

substLinePiece(X, ItX, PecaNova, [Elem | Resto], [Elem | Resto2]) :- ItX \= X,
                                                                     ItX1 is ItX + 1,
                                                                     substLinePiece(X, ItX1, PecaNova, Resto, Resto2).
                                                                                                                                         
changePlayer(1,2).
changePlayer(2,1).

changePiece(1,2).
changePiece(2,1).

changePecLeft(0,_,Board,Board,_, _).
changePecLeft(X,Y,Board, Board1,Piece,NewPiece) :- findPiece(Board,X,Y,A),
                                                   (A =:= NewPiece ->
                                                   substPiece(X, Y, Piece, Board, Board1);
                                                   substPiece(X, Y, A, Board, Board1)).

changePecTopCenter(X,Y,Board, Board1,Piece,NewPiece) :- findPiece(Board,X,Y,A),
                                                   (A =:= NewPiece ->
                                                   substPiece(X, Y, Piece, Board, Board1);
                                                   substPiece(X, Y, A, Board, Board1)).

changePecRight(9,_,Board,Board,_,_).
changePecRight(X,Y,Board, Board1,Piece,NewPiece) :- findPiece(Board,X,Y,A),
                                                  (A =:= NewPiece ->
                                                   substPiece(X, Y, Piece, Board, Board1);
                                                   substPiece(X, Y, A, Board, Board1)).

changePecTop(_,0,Board,Board,_,_).
changePecTop(X,Y,Board,NewB,Piece, NewPiece) :- X1 is X-1, X2 is X+1,
                             changePecLeft(X1,Y,Board, Board1,Piece,NewPiece),
                             changePecTopCenter(X,Y,Board1,Board2,Piece,NewPiece),
                             changePecRight(X2,Y,Board2,NewB,Piece,NewPiece).

changePecBottom(_,9,Board,Board,_,_).
changePecBottom(X,Y,Board,NewB,Piece, NewPiece) :- X1 is X-1, X2 is X+1,
                             changePecLeft(X1,Y,Board, Board1,Piece,NewPiece),
                             changePecTopCenter(X,Y,Board1,Board2,Piece,NewPiece),
                             changePecRight(X2,Y,Board2,NewB,Piece,NewPiece).


changePec(X,Y,Board,NewB) :- findPiece(Board,X,Y, Piece),
                          changePiece(Piece,NewPiece),
                          Y1 is Y - 1,
                          changePecTop(X,Y1,Board,Board1, Piece,NewPiece),
                          X1 is X-1,
                          X2 is X+1,
                          changePecLeft(X1,Y,Board1,Board2,Piece,NewPiece),
                          changePecRight(X2,Y,Board2,Board3,Piece,NewPiece),
                          Y2 is Y+1,
                          changePecBottom(X,Y2,Board3, NewB, Piece, NewPiece).
                          
contPoints(Board,Piece,C) :-  findall(Piece,findPiece(Board,_,_,Piece),L), length(L,C).

end(Board) :- findall(0,findPiece(Board,_,_,0),L), length(L,C),
                findall(1,findPiece(Board,_,_,1),M), length(M,B),
                findall(2,findPiece(Board,_,_,2),N), length(N,A),               
           (C =:= 0 | B == 0 | A == 0)
                   -> true;
              false.
                   
winner(Board,P1,P2,W) :- findall(P1,findPiece(Board,_,_,P1),L),length(L,A),
                                        findall(P2,findPiece(Board,_,_,P2),M),length(M,B),
                                         A >= B
                                        -> W is P1
                                        ; W is P2.

afterPass([],[],_).                
afterPass([H|T],[R|C],P) :- afterPassLine(H,R,P),
                                                afterPass(T,C,P).

afterPassLine([],[],_).                                         
afterPassLine([H|T],[R|C],P) :- H == 0
                                                -> R is P,                                              
                                                afterPassLine(T,C,P)
                                                ; R is H ,afterPassLine(T,C,P).


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%                      Jogadas                           %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

validMov(Xi,Yi,Xf,Yf,Board,D) :- Xf > 0, Xf < 9, Yf > 0, Yf < 9, (Xf \= Xi | Yf \= Yi),
              findPiece(Board,Xf,Yf,Pc),
              Pc == 0 ->
			  D is 1;
			  D is 0.

processCoords(Xi,Yi,Xf,Yf,Board,D,Player) :- repeat,
              write('Indique as coordenadas da peca que pretende mover no seguinte formato: "(X,Y)."'), nl,
              read((Xi, Yi)), % X e Y tem de ser >= 1 e <= 9
              Xi > 0, Xi < 9, Yi > 0, Yi < 9,
              findPiece(Board,Xi,Yi,P),
              P == Player,
              nl,
              write('Indique as coordenadas onde pretende colocar a peça no seguinte formato: "(X,Y)."'), nl,
              read((Xf, Yf)), % X e Y tem de ser >= 1 e <= 9
              Xf > 0, Xf < 9, Yf > 0, Yf < 9, (Xf \= Xi | Yf \= Yi),
              findPiece(Board,Xf,Yf,Pc),
              Pc == 0,
              dist(Xi,Yi,Xf,Yf,D),
              D < 3.
                          
readOpt(C) :- repeat,
                        write('Pretende jogar(1) ou passar(2): '),
                        read(C),
                        (C == 1 | C == 2).

dist(Xi,Yi,Xf,Yf, D) :- D is exp((exp((Xf-Xi),2) + exp((Yf - Yi),2)),1/2).
                 
singleMov(Xi,Yi,Xf,Yf,T,Newb) :-
             findPiece(T,Xi,Yi,P),
             substPiece(Xf,Yf,P,T,Newb).

combMov(Xi,Yi,Xf,Yf,T, Newb) :- findPiece(T,Xi,Yi,P),
                      substPiece(Xi,Yi,0,T, Board1),
                      substPiece(Xf,Yf,P,Board1, Newb).
                                          
pontuation(Board) :- write('Pontuacao do jogador1: '),
              contPoints(Board,1,P1), write(P1),nl,
              write('Pontuacao do jogador2: '),
              contPoints(Board,2,P2), write(P2),nl,nl.

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%                   Modos de Jogo                        %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

modeOne :- board(T), modeOne(T,1).

modeOne(T,P) :- (end(T)
                          -> showboard(T),
                          changePlayer(P,P2),
                          winner(T,P,P2,W),
                          write('Venceu o Jogador '),write(W),nl,
                          pontuation(T),
                          menu
                          ; nl,write('Vez do jogador '), write(P), nl,nl,
							showboard(T),
              nl,
                          readOpt(C),nl,
                          (2 =:= C
                          -> changePlayer(P,NewP),
                          afterPass(T,NewB,NewP),
                          write('Pontuacao do jogador1: '),
              contPoints(T,1,P1), write(P1),nl,
              write('Pontuacao do jogador2: '),
              contPoints(T,2,P2), write(P2),nl,nl,
                          modeOne(NewB,NewP)
              ;processCoords(Xi,Yi,Xf,Yf,T,D,P),
              (D < 2 ->
              singleMov(Xi,Yi,Xf,Yf,T,Newb);
              D < 3, D >= 2 ->
              combMov(Xi,Yi,Xf,Yf,T,Newb)),
              changePec(Xf,Yf,Newb,FinalB),
                          changePlayer(P, NewP),
              nl,
              pontuation(FinalB),
              modeOne(FinalB,NewP))).
                          
                          
modeTwo :- board(T), modeTwo(T,2).

modeTwo(T,P) :- (end(T)
                          -> showboard(T),
                          changePlayer(P,P2),
                          winner(T,P,P2,W),
                          write('Venceu o Jogador '),write(W),nl,
                          pontuation(T),
                          menu
                          ; nl,write('Vez do jogador '), write(P), nl,nl,
              showboard(T),
              nl,
                          (P == 2
                          -> aI(T,FinalB,P,0),
                          changePlayer(P, NewP),
              nl,
              pontuation(FinalB),
              modeTwo(FinalB,NewP)
                          ;readOpt(C),nl,
                          (2 =:= C
                          -> changePlayer(P,NewP),
                          afterPass(T,NewB,NewP),
                          write('Pontuacao do jogador1: '),
              contPoints(T,1,P1), write(P1),nl,
              write('Pontuacao do jogador2: '),
              contPoints(T,2,P2), write(P2),nl,nl,
                          modeTwo(NewB,NewP)
              ;processCoords(Xi,Yi,Xf,Yf,T,D,P),
              (D < 2 ->
              singleMov(Xi,Yi,Xf,Yf,T,Newb);
              D < 3, D >= 2 ->
              combMov(Xi,Yi,Xf,Yf,T,Newb)),
              changePec(Xf,Yf,Newb,FinalB),
                          changePlayer(P, NewP),
              nl,
              pontuation(FinalB),
              modeTwo(FinalB,NewP)))).

modeAI :- board(B),modeAI(B,1).                   
modeAI(T,P) :- (end(T)
                          -> showboard(T),
                          changePlayer(P,P2),
                          winner(T,P,P2,W),
                          write('Venceu o Jogador '),write(W),nl,
                          pontuation(T),
                          menu
                          ; nl,write('Vez do jogador '), write(P), nl,nl,
              showboard(T),
              nl,
                          aI(T,FinalB,P,0),
                          changePlayer(P, NewP),
              nl,
              pontuation(FinalB),
              modeAI(FinalB,NewP)).
                          
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%                          AI                            %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%%%A Parte da Inteligencia Artificial foi elaborada em colaboracao com o grupo 8.

aI(Board,FinalB,Piece,9999):- changePlayer(Piece,NewPiece),afterPass(Board,FinalB,NewPiece).
aI(Board,FinalB,Piece,Count):-
               Count2 is Count+1,
          
               random(1, 9, X),
               random(1, 9, Y),
               
               findPiece(Board,X,Y,P),
               ((P == Piece, test(Piece,Board,X,Y,8,8,8,Estado,X0,Y0),

               ((Estado=true,verifJog(Piece,Board,X,Y,X0,Y0,Resultado),

                           ((Resultado=criar,singleMov(X,Y,X0,Y0,Board,Newb),changePec(X0,Y0,Newb,FinalB))|

                           (Resultado=saltar,combMov(X,Y,X0,Y0,Board,Newb),changePec(X0,Y0,Newb,FinalB))))|

               (Estado=false,aI(Board,FinalB,Piece,Count2))))|

               (Piece \= P,aI(Board,FinalB,Piece,Count2))).                                     
                
test(_,_,_,_,_,0,_,false,_,_):-!.

test(Piece,Board,X,Y,X0,Y0,_,true,X0,Y0):-
          verifJog(Piece,Board,X,Y,X0,Y0,Res),
          Res\=erro,!.

test(Piece,Board,X,Y,X0,Y0,Size,Result,X2,Y2):-
          X02 is X0-1,
          ((X02=0,X0f is Size,Y0f is Y0-1)|
          (X02\=0,X0f is X02,Y0f is Y0)),
          test(Piece,Board,X,Y,X0f,Y0f,Size,Result,X2,Y2).

                
verifJog(Piece,Board,X,Y,X0,Y0,criar):-
        X>0,X=<8,X0>0,X0=<8,
        Y>0,Y=<8,Y0>0,Y0=<8,
        findPiece(Board,X,Y,P),
        findPiece(Board,X0,Y0,0),
        Piece = P,
        dist(X,Y,X0,Y0,D),
        D >= 1, D < 2,!.

verifJog(Piece,Board,X,Y,X0,Y0,saltar):-
        X>0,X=<8,X0>0,X0=<8,
        Y>0,Y=<8,Y0>0,Y0=<8,
        findPiece(Board,X,Y,P),
        findPiece(Board,X0,Y0,0),
        Piece = P,
        dist(X,Y,X0,Y0,D),
        D >= 2, D < 3,!.

verifJog(_,_,_,_,_,_,erro).



%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                                                        %
%                         Menu                           %
%                                                        %
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

readOption(C) :- repeat,
                        write('Opção: '),
                        read(C),
                        (C == 1 | C == 2 | C == 3 | C == 4),!.
                        
menu :- write('Bem-Vindo ao BLOB WARS'),nl,nl,
        write('Escolha uma opção'),nl,
        write('1. Modo Humano vs Humano'),nl,
        write('2. Modo Humano vs IA'),nl,
        write('3. Modo IA vs IA'),nl,
        write('4. Sair'),nl,
        readOption(C),
        option(C).
        
option(1) :- modeOne.
option(2) :- modeTwo.
option(3) :- modeAI.
option(4) :- !.




