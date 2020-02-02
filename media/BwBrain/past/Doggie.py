#
namespace DoggieDemo

#Random Forward Movement
class RandomMove()
    def __init__(random-move :name $n :speed $s :time $t)
       parallel:
            translate :speed $s :time $t
            animate :name $n :speed 1.0 :loop true
            waitfor :time $t

#Random Turning
class RandomTurn()
    def __init__(random-turn :time $t)
        probability_select:
            1.0
                parallel:
                    rotate :degree 1.0
                    animate :name "TurnLeft" :speed 1.0 :loop true
                    waitfor :time $t :random $t
            1.0    
                parallel:
                    rotate :degree -1.0
                    animate :name "TurnRight" :speed 1.0 :loop true
                    waitfor :time $t :random $t

#Passive Dog Behaviors
class Passive ()
    def __init__(passive)
        probability_select:
            1.0    
                animate :name "Sitting" :speed .34 :loop false
            1.0    
                animate :name "LayingIdle" :speed .67 :loop false

#Active Dog Behaviors
class Active ()
    def __init__(active)
        probability_select:
            1.0    
                fail #fail occasionally - give other behaviors a chance.
            .25
                animate :name "ChaseTail" :speed 1.0 :loop true
            5.0    
                sequence:
                    random-turn :degree 1.0
                    random-move :speed 4.0

#Bodily Behaviors
class Bodily ()
    def __init__(bodily)
        probability_select:
            20.0
                fail #fail occasionally - give other behaviors a chance.
            2.0
                sequence:
                    animate :name "LayingIdle" :speed .2 :loop false
                    animate :name "Sleeping" :speed .2 :loop false
            4.0
                sequence:
                    random-turn :time 1.5
                    random-move :name "StalkingPrey" :speed 8.0 :time 0.5
                    animate :name "Peeing" :speed 1.0 :loop false
                    random-turn :time 1.5
                    random-move 6.0 :name "JumpyRun" :speed 2.0
           4.0
                sequence:
                    animate :name "ScratchingBack" :speed 1.0 :loop false
                    animate :name "Scratching" :speed 1.0 :loop false

#Root Behavior
class Behave ()
    def __init__(behave)
        priority_select :repeat true:
            bodily
            active
            passive
