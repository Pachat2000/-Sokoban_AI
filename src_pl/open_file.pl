sokoban(X):-open(X, read, Str),
    read_file(Str,Lines),
    close(Str),boxpos(Lines,BoxPoint,0,Posj),li(BoxPoint,ListBox),write(Posj),right(Posj,L),possible(Lines,L,H).

read_file(Stream,[]) :-
    at_end_of_stream(Stream).

read_file(Stream,[X|L]) :-
    read_line_to_string(Stream, A),
    atom_chars(A,X),
    read_file(Stream,L).


boxpos([],_,_,_).
boxpos([X|L],BoxPoint,Py,Posj):-Py2 is Py+1,boxlpos(X,BoxPoint,Py,0,Posj),boxpos(L,BoxPoint,Py2,Posj).

boxlpos([],_,_,_,_).
boxlpos([X|L],BoxPoint,Py,Px,[A,B]):-(X=='$'->append(More,[Px,Py],BoxPoint),Px2 is Px+1,boxlpos(L,More,Py,Px2,[A,B]);X=='1'->A is Px,B is Py,Px2 is Px+1,boxlpos(L,BoxPoint,Py,Px2,[A,B]);Px2 is Px+1,boxlpos(L,BoxPoint,Py,Px2,[A,B])).

li([],[]).
li([A,B|T],[[X,Z]|ListBox]):-X is A,Z is B,li(T,ListBox).