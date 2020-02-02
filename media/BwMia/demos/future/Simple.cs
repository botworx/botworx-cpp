predicate weight(int)

class Test : Solver {
    //forward chaining rule
    rule ($x is foo) {
        action {
            $x has $y
            $y is bar
            -->
            $y is foo
        }
    }
    //backward chaining rule
    rule (? $x is bar) {
        action {
            $x has $y
            $y is foo
            -->
            return True
        }
    }
}