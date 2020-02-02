class Test:
    rule ($x is foo): #forward chaining rule
        action:
            $x has $y
            $y is bar
            -->
            $y is foo
    rule (? $x is bar): #backward chaining rule
        action:
            $x has $y
            $y is foo
            -->
            return True
