
#Let's assume this achieve goal is added to the event queue.
+! my-cat eat food-x ;

#achieve the goal of eating ?f
method (+! my-cat eat ?f) :
    rule :
        -->
        ? my-cat likes ?f ; # test to see if my-cat likes ?f
        + my-cat [eat] = ?f ; # okay, eat it!
    
#My cat really likes good food.
method (+? my-cat likes ?f) : #the triggering event
    rule :
        ?f is-a good.food # a precondition
        -->
        + my-cat really.likes ?f #an assertion

#My cat somewhat likes mediocre food.
method (@+? my-cat likes ?f) :
    rule :
        ?f is-a mediocre.food
        -->
        @+ my-cat somewhat.likes ?f
    )
)

#My cat doesn't like bad food.
method (@+? my-cat likes ?f) :
    (rule
        (?f is-a bad.food)
        -->
        @+ (my-cat not.likes ?f)
    )
)

//My very hungry cat somewhat likes bad food.
(method @+? (my-cat likes ?f)
    (rule
        (my-cat is very.hungry)
        (?f is-a bad.food)
        -->
        @+ (my-cat somewhat.likes ?f)
    )
)