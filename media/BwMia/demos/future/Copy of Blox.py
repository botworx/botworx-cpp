'''
Blox : Mia Blocks World Implementation

'''

method Main () :
    rule :
        $g type goal
        not: ($g is achieved)
        -->
        ! $agent achieve $g

method AllGoals ($g is achieved) :
    rule :
        $g type goal
        $g1 type goal
        $g1 is achieved
        ==>
        halt

method StackerPropose (! $agent achieve $g) :
    rule :
        $g object $b1
        $g destination $b2
        $b1 on-top $b2
        -->
        $g is achieved
        $self benefit 2
        ==>
        return

    rule :
        $g object $b1
        $g destination $b2
        -->
        ! $agent stack $b1 destination: $b2

method ClearPropose ($agent clear $x)
    rule :
        $x beneath $y
        $z is clear
        $z <> $x
        $z <> $y
        -->
        ! :agent stack $y
            destination $z

#StackerApply
method :agent stack $x
    (rule
        (not($x is clear))
        -->
        (propose (:agent clear $x))
        ==>
        return
    )	
    (rule
        (:thought destination $y)
        (not($y is clear))
        -->
        (propose (:agent clear $y))
        ==>
        return
    )		
    (rule
        ($x on-top $z)
        -->
        (retract ($x on-top $z))
    )
    (rule
        (:thought destination $y)
        -->
        (assert ($x on-top $y))
    )
)
(method NotOnTopElab ($x on-top $y -1)
    (rule
        ($y beneath $x)
        -->
        (retract ($y beneath $x))
    )
    (rule
        ==>
        (assert ($y is clear))			
    )
)
(method OntopElab ($x on-top $y)
    (rule
        ($y type block)		
        ($y is clear)
        -->
        (retract ($y is clear))
    )
    (rule
        ($x on-top $y)
        -->
        (assert ($y beneath $x))
    )
)

(problem Blox
	(topic Table-1
		(type table)
		(is clear)
	)
	(topic Block-1
		(type block)
		(on-top Table-1)
		(is clear)
	)
	(topic Block-2
		(type block)
		(on-top Block-1)
		(is clear)
	)
	(topic Block-3
		(type block)
		(on-top Block-2)
		(is clear)
	)
	(topic Goal-1
		(type goal)
		(action move)
		(object Block-1)
		(destination Block-2)
	)
	(topic Goal-2
		(type goal)
		(action move)
		(object Block-2)
		(destination Block-3)
	)
)