;
; External State Manipulation
;
(domain SiblingQuery ()
	(method main ()
		(rule
			-->
            (:agent find-sibling billy)            
		)
	)
    (method SiblingFinder (:agent find-sibling $x)
        (rule
			(select $x (parent $p) :space $$)
			(select $y (parent $p) :space $$)
			($y <> $x)
            -->
            ($x sibling $y)
            (print)
            ==>
            halt
        )
    )    
)
(frame family
	(topic Mary
		(type person)
		(family Smith)
		(spouse John)
		(child Billy)
		(child Suzy)		
	)
	(topic John
		(type person)
		(family Smith)
		(spouse Mary)
		(child Billy)
		(child Suzy)
	)
	(topic Billy
		(type person)
		(family Smith)
		(parent John)
		(parent Mary)
	)
	(topic Suzy
		(type person)
		(family Smith)
		(parent John)
		(parent Mary)
	)
	(topic Smith
		(type family)
	)
)
(problem SiblingQuery
	(topic John (type person))
	(topic Mary (type person))
	(topic Billy (type person))
	(topic Suzy (type person))
)