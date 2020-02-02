method (? grass is wet)
    name: Blah
    rule:
        sky is raining
        -->
        true

method (? grass is wet)
    name: Blah
    rule:
        sprinkler is on
        -->
        true

constraint (? grass is wet)
    name: Blah
    rule:
        sky is raining
        sun is shining
        -->
        false


Grass is wet if it rained.
Grass is wet if the sprinkler was on.
The sun was shining.