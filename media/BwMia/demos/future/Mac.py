""" 
BwAi - Missionaries and Cannibals 
Based on the Soar Version 
Kurtis B Fields - 2008
""" 
class Mac () :
	def main () :
		#state success
		rule :
			$g type goal
			$g object $bank
			$g missionaries $m1
			$bank missionaries $m2
			$m1 = $m2
			$g cannibals $c1
			$bank cannibals $c2
			$c1 = $c2
			$g boat $b1
			$bank boat $b2
			$b1 = $b2
			==>
			halt
        #state failure
		rule :
			Bank-1 missionaries $m1
			$m1 > 0
			Bank-1 cannibals $c1
			$m1 < $c1
			-->
			$self fail "Too many cannibals on Bank1!!!" # assume 'assert/+'
			==>
			fail
		#state failure
		rule :
			Bank-2 missionaries $m2
			$m2 > 0
			Bank-2 cannibals $c2
			$m2 < $c2
			-->
			$self fail "Too many cannibals on Bank2!!!"
			==>
			fail
		#state failure
		rule :
			$self.parent.goal 
                missionaries $m1
                cannibals $c1
			$self.goal missionaries $m2 # .goal --> .operator?
			$m1 = $m2
			$self.goal cannibals $c2
			$c1 = $c2
			-->
			$self fail "State undoes parent goal!!!"
			==>
			fail
		rule :
			g type goal
			not: ($g is achieved)
			-->
			! $agent achieve $g
            
	def MoveMissionaryPropose (! $agent achieve $g) :
		rule :
			$bank1 type bank
			$bank1 boat $boat
			$bank1 missionaries $m
			$m > 0
			$bank2 type bank
			$bank2 <> $bank1
			-->
			propose :
                ! $agent move-boat $boat 
                    missionaries 1
                    cannibals 0
                    source $bank1
                    destination $bank2

    def MoveCannibalPropose (! $agent achieve $g) :
		rule :
			$bank1 type bank
			$bank1 boat $boat
			$bank1 cannibals $c
			$c > 0
			$bank2 type bank
			$bank2 <> $bank1
			-->
			propose :
                ! $agent move-boat $boat 
                    missionaries 0
                    cannibals 1
                    source $bank1
                    destination $bank2

    def MoveMissionariesPropose (! $agent achieve $g) :
		rule :
			$bank1 type bank
			$bank1 boat $boat
			$bank1 missionaries $m
			$m > 1
			$bank2 type bank
			$bank2 <> $bank1
			-->
			propose :
                ! $agent move-boat $boat 
                    missionaries 2
                    cannibals 0
                    source $bank1
                    destination $bank2

    def MoveCannibalsPropose (! $agent achieve $g) :
		rule :
			$bank1 type bank
			$bank1 boat $boat
			$bank1 cannibals $c
			$c > 1
			$bank2 type bank
			$bank2 <> $bank1
			-->
			propose :
                ! $agent move-boat $boat 
                    missionaries 0
                    cannibals 2
                    source $bank1 
                    destination $bank2

    def MoveMissionaryCannibalPropose (! $agent achieve $g) :
		rule :
			$bank1 type bank
			$bank1 boat $boat
			$bank1 missionaries $m
			$m > 0
			$bank1 cannibals $c
			$c > 0
			$bank2 type bank
			$bank2 <> $bank1
			-->
			propose :
                ! $agent move-boat $boat 
                    missionaries 1 
                    cannibals 1 
                    source $bank1 
                    destination $bank2

    def MoveBoatApply (! $agent move-boat $boat (source $bank1) (destination $bank2) (missionaries $m) (cannibals $c)) :
		rule :
			$bank1 missionaries $m1
			$bank2 missionaries $m2
			$bank1 cannibals $c1
			$bank2 cannibals $c2
			-->
            - $bank1 boat $boat
            - $bank1 missionaries $m1
            - $bank2 missionaries $m2
            - $bank1 cannibals $c1
            - $bank2 cannibals $c2
            $bank2 boat $boat	
            $bank1 missionaries [$m1 - $m]
            $bank2 missionaries [$m2 + $m]
            $bank1 cannibals [$c1 - $c]
            $bank2 cannibals [$c2 + $c]
"""
"""
problem Mac :

	frame Boat-1 :
		type boat

    frame Bank-1 :
		type bank
		missionaries 3
		cannibals 3
		boat Boat-1

    frame Bank-2 :
		type bank
		missionaries 0
		cannibals 0

    frame Goal-1 :
		type goal
		object Bank-2
		missionaries 3
		cannibals 3
		boat Boat-1
