# 2D-Physics-Pinball
 Alexandre Carreras, Carlos Arnau and Albert Chica pinball game for Physics II

 The .exe file is inside the game folder with the .dll

 Github Project Link:
 https://github.com/TheGewehr/B-platformer

 Controls:

 Left arrow -> Left flipper
 Right arrow -> Right flipper
 Down arrow -> Use spring
 I key -> Restart when you win or loose
 F1 key -> See all colliders

"Exiting" things that will make you enjoy the game:

- Betrayer Bumpers (they really are traitors)
- Very welcommed MLG surprising sounds
- A terribly innovative points counter :-/
- A relaxing background music

Dev's diary:

This project sounded easy, i mean, what could have gone wrong?
A lot of things, but not ones that you can solve in code, the ones that make you want to quit the university, environement errors
Gitignore, Properties... those were my nightmares until the last moment

But lets get to the important: 
- We created a world that gave some bugs beacose some vertex where too close
- Tryed to apply force unsuccesfully (so we used set linear impulse if i remember well)
- Then created the flippers in a smart way (so we don't have to use fixtures)
- We had the marvelous idea to get the sounds effects to make it more interesting
- Then we discovered that OnCollision wasn't called when the ball was colliding with the map, so we tried to add it to a collider list (strangelly unsuccessfull)
- Solved last buggs that were causing memory leacks and voila, a pinball game


 Don't use headphones...
