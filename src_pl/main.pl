top(c2r5,c2r4). 
top(c2r6,c2r5). 
top(c3r3,c3r2). 
top(c3r4,c3r3).
top(c3r5,c3r4). 
top(c3r6,c3r5). 
top(c5r5,c5r4). 
top(c5r6,c5r5). 
top(c6r3,c6r2). 
top(c6r4,c6r3). 
top(c6r5,c6r4). 
top(c7r4,c7r3). 
top(c7r5,c7r4). 

right(c3r2,c4r2). 
right(c3r6,c4r6).
right(c4r2,c5r2). 
right(c4r6,c5r6).
right(c5r2,c6r2).
right(c6r3,c7r3). 
right(c2r4,c3r4).
right(c3r4,c4r4).
right(c4r4,c5r4). 
right(c5r4,c6r4). 
right(c6r4,c7r4). 
right(c2r5,c3r5).
right(c5r5,c6r5).
right(c5r5,c6r5).
right(c6r5,c7r5). 
right(c2r6,c3r6).

sokoban(c4r6).

storage(c4r4).
storage(c3r4).
storage(c3r3).

box(c5r5).
box(c5r4).
box(c6r3).

neib(Loc1,Loc2,up):-top(Loc1,Loc2).
neib(Loc1,Loc2,down):-top(Loc2,Loc1).
neib(Loc1,Loc2,right):-right(Loc1,Loc2).
neib(Loc1,Loc2,left):-right(Loc2,Loc1).

goal_reached([]).
goal_reached([Loc|Locs]):-
    storage(Loc),
    goal_reached(Locs).

reachable_by_sokoban(Loc,Loc,_BoxLocs).
reachable_by_sokoban(Loc1,Loc2,BoxLocs):-
    neib(Loc1,Loc3,_),
    \+ member(Loc3,BoxLocs),
    reachable_by_sokoban(Loc3,Loc2,BoxLocs).

stuck(X,Y):-
    (right(X,Y);right(Y,X)),
    (\+ storage(X); \+ storage(Y)),
    (\+ top(X,_), \+ top(Y,_);
    \+ top(_,X), \+ top(_,Y)),!.
stuck(X,Y):-
    (top(X,Y);top(Y,X)),
    (\+ storage(X); \+ storage(Y)),
    (\+ right(X,_), \+ right(Y,_);
    \+ right(_,X), \+ right(_,Y)),!.
    
corner(Position):- \+(right(Position, _)), \+(top(Position, _)).
corner(Position):- \+(right(_, Position)), \+(top(Position, _)).
corner(Position):- \+(right(Position, _)), \+(top(_, Position)).
corner(Position):- \+(right(_, Position)), \+(top(_, Position)).

loop_box(_,[]).
loop_box(Loc,[H|T]) :-
    \+ stuck(H, Loc),
    loop_box(Loc,T).

good_dest(Loc,BoxLocs):-
	\+(member(Loc,BoxLocs)),
	storage(Loc), 
	loop_box(Loc,BoxLocs).
good_dest(Loc,BoxLocs):- 
    \+(member(Loc,BoxLocs)),
    \+(corner),
    loop_box(Loc,BoxLocs).
    

