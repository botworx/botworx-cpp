;
(behavior DoggieDemo

;Random Forward Movement
(behavior RandomMove (+! .agent random-move :name $n :speed $s :time $t)
    (method ()
        -->
       (parallel
            (+! .agent translate :speed $s :time $t)
            (+! .agent animate :name $n :speed 1.0 :loop true) 
            (+! .agent waitfor :time $t) 
       )
    )
)

;Random Turning
(behavior RandomTurn (+! .agent random-turn :time $t)
    (method ()
        -->
        (probability-selector
            (1.0    
                (parallel
                    (+! .agent rotate :degree 1.0)
                    (+! .agent animate "TurnLeft" :speed 1.0 :loop true)
                    (+! .agent waitfor :time $t :random $t)
                )
            )
            (1.0    
                (parallel
                    (+! .agent rotate :degree -1.0)
                    (+! .agent animate :name "TurnRight" :speed 1.0 :loop true)
                    (+! .agent waitfor :time $t :random $t)
                )
            )
        )
    )
)  

;Passive Dog Behaviors
(behavior Passive (+! .agent passive ())
    (method ()
        -->
        (probability-selector
            (1.0    
                (+! .agent animate :name "Sitting" :speed .34 :loop false)
            )
            (1.0    
                (+! .agent animate :name "LayingIdle" :speed .67 :loop false)
            )        
        )
    )
)
;Active Dog Behaviors
(behavior Active (+! .agent active ())
    (method ()
        -->
        (probability-selector
            (1.0    
                (fail) ;fail occasionally - give other behaviors a chance.
            )
            (.25
                (+! .agent animate :name "ChaseTail" :speed 1.0 :loop true)
            )
            (5.0    
                (sequence
                    (+! .agent random-turn :degree 1.0)
                    (+! .agent random-move :speed 4.0)
                )
            )        
        )
    )
)    
;Bodily Behaviors
(behavior bodily ()
    (method ()
        -->
        (probability-selector
            (20.0
                (fail) ;fail occasionally - give other behaviors a chance.
            )
            (2.0
                (sequence
                    (+! .agent animate :name "LayingIdle" :speed .2 :loop false)
                    (+! .agent animate :name "Sleeping" :speed .2 :loop false)
                )
            )        
            (4.0
                (sequence
                    (+! .agent random-turn :time 1.5)
                    (+! .agent random-move :name "StalkingPrey" :speed 8.0 :time 0.5)
                    (+! .agent animate :name "Peeing" :speed 1.0 :loop false)
                    (+! .agent random-turn :time 1.5)
                    (+! .agent random-move 6.0 :name "JumpyRun" :speed 2.0)
                )
            )
           (4.0
                (sequence
                    (+! .agent animate :name "ScratchingBack" :speed 1.0 :loop false)
                    (+! .agent animate :name "Scratching" :speed 1.0 :loop false)
                )
            )
        )
    )
)
;Root Behavior
(behavior behave ()
    (priority-selector :repeat true
        (+! .agent bodily ())
        (+! .agent active ())
        (+! .agent passive ())
    )
)

) ; (behavior DoggieDemo

;Hmmm...
(problem DoggieDemo
)
