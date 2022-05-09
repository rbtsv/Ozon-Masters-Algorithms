#@c = "({g},({w}),({b},({w}),({g},({w}))),({b},({w})))"

@c = gets

#puts @c

#@c ||= "([level0]{$-95_{1}$}([level1]{$-80_{2}$}([level2]{$-69_{4}$}([level3]{$-31_{8}$}([level4]{$64_{16}$}) ([level4]{$-31_{17}$}) ) ([level3]{$-69_{9}$}([level4]{$-69_{18}$}) ([level4]{$-9_{19}$}) ) ) ([level2]{$-80_{5}$}([level3]{$-80_{10}$}([level4]{$-21_{20}$}) ([level4]{$-80_{21}$}) ) ([level3]{$-72_{11}$}([level4]{$-72_{22}$}) ([level4]{$-60_{23}$}) ) ) ) ([level1]{$-95_{3}$}([level2]{$-95_{6}$}([level3]{$-95_{12}$}([level4]{$-11_{24}$}) ([level4]{$-95_{25}$}) ) ([level3]{$10050000000_{13}$}([level4]{$10050000000_{26}$}) ([level4]{$10050000000_{27}$}) ) ) ([level2]{$10050000000_{7}$}([level3]{$10050000000_{14}$}([level4]{$10050000000_{28}$}) ([level4]{$10050000000_{29}$}) ) ([level3]{$10050000000_{15}$}([level4]{$10050000000_{30}$}) ([level4]{$10050000000_{31}$}) ) ) ) )"

@c = @c.strip

#@c = " ({-2} ({-2} ({-2} ({1})  ({-2}) )  ({3} ({3})  ({4}) ) )  ({1} ({1} ({1})  ({100500}) )  ({100500} ({100500})  ({100500}) ) ) ) "
#@c = @c.strip



#@base_style = "shape=rectangle, rounded corners, draw, align=center, top color=white, bottom color=blue!20"
#@l1_style = @base_style + ", style={level distance=12cm, sibling angle=170, counterclockwise from=185}"
#@l2_style = @base_style + ", style={level distance=6cm, sibling angle=160, counterclockwise from=190}"
#@l3_style = @base_style + ", style={level distance=3cm, sibling angle=120, counterclockwise from=210}"
#@l4_style = @base_style + ", style={level distance=0.5cm, sibling angle=45, counterclockwise from=247.5}"

@style4='
\tikzset{level1/.style={level distance=11cm, sibling angle=170, counterclockwise from=185}		}
\tikzset{level2/.style={level distance=6cm, sibling angle=160, counterclockwise from=190}		}
\tikzset{level3/.style={level distance=3cm, sibling angle=120, counterclockwise from=210}		}
\tikzset{level4/.style={level distance=2cm, sibling angle=80, counterclockwise from=230}		}
'
@style3='
\tikzset{level1/.style={level distance=6cm, sibling angle=160, counterclockwise from=190}		}
\tikzset{level2/.style={level distance=3cm, sibling angle=120, counterclockwise from=210}		}
\tikzset{level3/.style={level distance=2cm, sibling angle=80, counterclockwise from=230}		}
'




@c[@c.size()-1]=''
@c.gsub!(",", "\n")
#@c.gsub!("(g", "([dra{w}, fill=gray!30] {gray}")
#@c.gsub!("({w}", "([dra{w}, fill={w}hite!30] {{w}hite}")
#@c.gsub!("(b", "([dra{w}, fill=black!50]{black}")
@c[0]='';
@c.gsub!("(", "child{ node")
@c.gsub!(")", "}")

@tree = "\\node" + @c + ";"

@tree.gsub!("10050000000", "+\\infty")
#@tree.gsub!("d0", @l1_style)
#@tree.gsub!("d1", @l2_style)
#@tree.gsub!("d2", @l3_style)
#@tree.gsub!("d3", @l4_style)
#@tree.gsub!("d4", @l4_style)

(0..4).each{ |l| @tree.gsub!("child{ node[level#{l}]", "child[level#{l}]{ node")}

@level3 = @tree["level4"].nil?

@tpl = File.open("ex_tree_tpl.tex").read

@tpl.gsub!("%%%TREE%%%", @tree);



@tpl.gsub!("%%%TREE%%%", @tree);

@level3 ? @tpl.gsub!("%%%STYLE%%%", @style3) : @tpl.gsub!("%%%STYLE%%%", @style4) 

#puts @tpl

@dir = "./"

File.open(@dir+"tree.tex", "w+"){|f| f.write @tpl }
%x{/Library/TeX/texbin/pdflatex #{@dir}tree.tex && open #{@dir}tree.pdf}

