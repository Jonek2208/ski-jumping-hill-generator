# Ski jumping hill generator

Program generates ski jumping hill model in wavefront .obj format using xml input.



# Xml example

```xml
<?xml version="1.0" encoding="utf-8"?>
<hill id="Zakopane HS105" profile-type="ICR2008">
    <inrun gates="35" e="91.57" es="17.94" r1="94" t="6.45" gamma="35" alpha="10.5" b1="2.8"/>
    <landinghill w="95" hs="105" h="44.64" n="82.7" s="2.36" l1="10" l2="10" rl="210" r2l="120" r2="90" beta0="5.83333349" betap="35" betak="32.5" betal="29.75" b2="7.0" bk="19.0" bu="21.0"/>
    <outrun a="100" ra="0" betaa="0"/>
</hill>
```

# Nodes
## hill
attributes:
- `id: string` - hill name
- `profile-type: 0 | 1 | 2` - hill profile type (default 0)

### inrun
attributes:
- `gates: int` - number of gates
- `e: double` - length of the inrun part without take-off table
- `es: double` - length of the inrun between highest and lowest starting gate
- `r1: double` - radius of the transition curve measured at the end
- `t: double` - length of the take-off table
- `gamma: double` - inclination of the inrun (in degrees)
- `alpha: double` - inclination of the take-off table (in degrees)
- `b1: double` - width of the inrun

### landinghill
attributes:
- `w: double` - k-point of the hill
- `hs: double` - hill size
- `h: double` - height difference between take-off table edge and K point
- `n: double` - horizontal distance between take-off table edge and K point
- `s: double` - height of the take-off table
- `[ICR1992] l1: double` - length of the hill between P and K
- `l2: double` - length of the hill between K and L
- `[ICR1996 | ICR2008] rl: double` - radius of the landing area curve at P-L
- `[ICR2008] r2l: double` - radius of the transition curve from L to U at L
- `r2: double` - radius of the transition curve from L to U at U
- `beta0: double` - tangent angle of the landing hill at the base of the take-off (in degrees)
- `[ICR1996 | ICR2008] betap: double` - tangent angle at P point (in degrees)
- `betak: double` - tangent angle at K point (in degrees)
- `[ICR1996 | ICR2008] betal: double` - tangent angle at L point (in degrees)
- `b2: double` - width of the landing hill at the base of the take-off
- `bk: double` - width of the landing hill at K point
- `bu: double` - width of the landing hill at U point
### outrun
attributes:
- `a: double` - length of the outrun
- `r2: double` - radius of the outrun counter-slope curve (only applicable if `betaa != 0`)
- `betaa: double` - tangent angle of the outrun counter-slope (in degrees, positive if slope is rising)
