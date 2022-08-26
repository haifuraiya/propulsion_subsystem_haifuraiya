<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE eagle SYSTEM "eagle.dtd">
<eagle version="6.5.0">
<drawing>
<settings>
<setting alwaysvectorfont="no"/>
<setting verticaltext="up"/>
</settings>
<grid distance="0.1" unitdist="inch" unit="inch" style="lines" multiple="1" display="yes" altdistance="0.01" altunitdist="inch" altunit="inch"/>
<layers>
<layer number="1" name="Top" color="4" fill="1" visible="no" active="no"/>
<layer number="2" name="Route2" color="1" fill="3" visible="no" active="no"/>
<layer number="3" name="Route3" color="4" fill="3" visible="no" active="no"/>
<layer number="14" name="Route14" color="1" fill="6" visible="no" active="no"/>
<layer number="15" name="Route15" color="4" fill="6" visible="no" active="no"/>
<layer number="16" name="Bottom" color="1" fill="1" visible="no" active="no"/>
<layer number="17" name="Pads" color="2" fill="1" visible="no" active="no"/>
<layer number="18" name="Vias" color="2" fill="1" visible="no" active="no"/>
<layer number="19" name="Unrouted" color="6" fill="1" visible="no" active="no"/>
<layer number="20" name="Dimension" color="15" fill="1" visible="no" active="no"/>
<layer number="21" name="tPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="22" name="bPlace" color="7" fill="1" visible="no" active="no"/>
<layer number="23" name="tOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="24" name="bOrigins" color="15" fill="1" visible="no" active="no"/>
<layer number="25" name="tNames" color="7" fill="1" visible="no" active="no"/>
<layer number="26" name="bNames" color="7" fill="1" visible="no" active="no"/>
<layer number="27" name="tValues" color="7" fill="1" visible="no" active="no"/>
<layer number="28" name="bValues" color="7" fill="1" visible="no" active="no"/>
<layer number="29" name="tStop" color="7" fill="3" visible="no" active="no"/>
<layer number="30" name="bStop" color="7" fill="6" visible="no" active="no"/>
<layer number="31" name="tCream" color="7" fill="4" visible="no" active="no"/>
<layer number="32" name="bCream" color="7" fill="5" visible="no" active="no"/>
<layer number="33" name="tFinish" color="6" fill="3" visible="no" active="no"/>
<layer number="34" name="bFinish" color="6" fill="6" visible="no" active="no"/>
<layer number="35" name="tGlue" color="7" fill="4" visible="no" active="no"/>
<layer number="36" name="bGlue" color="7" fill="5" visible="no" active="no"/>
<layer number="37" name="tTest" color="7" fill="1" visible="no" active="no"/>
<layer number="38" name="bTest" color="7" fill="1" visible="no" active="no"/>
<layer number="39" name="tKeepout" color="4" fill="11" visible="no" active="no"/>
<layer number="40" name="bKeepout" color="1" fill="11" visible="no" active="no"/>
<layer number="41" name="tRestrict" color="4" fill="10" visible="no" active="no"/>
<layer number="42" name="bRestrict" color="1" fill="10" visible="no" active="no"/>
<layer number="43" name="vRestrict" color="2" fill="10" visible="no" active="no"/>
<layer number="44" name="Drills" color="7" fill="1" visible="no" active="no"/>
<layer number="45" name="Holes" color="7" fill="1" visible="no" active="no"/>
<layer number="46" name="Milling" color="3" fill="1" visible="no" active="no"/>
<layer number="47" name="Measures" color="7" fill="1" visible="no" active="no"/>
<layer number="48" name="Document" color="7" fill="1" visible="no" active="no"/>
<layer number="49" name="Reference" color="7" fill="1" visible="no" active="no"/>
<layer number="51" name="tDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="52" name="bDocu" color="7" fill="1" visible="no" active="no"/>
<layer number="91" name="Nets" color="2" fill="1" visible="yes" active="yes"/>
<layer number="92" name="Busses" color="1" fill="1" visible="yes" active="yes"/>
<layer number="93" name="Pins" color="2" fill="1" visible="no" active="yes"/>
<layer number="94" name="Symbols" color="4" fill="1" visible="yes" active="yes"/>
<layer number="95" name="Names" color="7" fill="1" visible="yes" active="yes"/>
<layer number="96" name="Values" color="7" fill="1" visible="yes" active="yes"/>
<layer number="97" name="Info" color="7" fill="1" visible="yes" active="yes"/>
<layer number="98" name="Guide" color="6" fill="1" visible="yes" active="yes"/>
</layers>
<schematic xreflabel="%F%N/%S.%C%R" xrefpart="/%S.%C%R">
<libraries>
<library name="mpnl_holes">
<description>&lt;b&gt;Mounting Holes and Pads&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="2,8-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 2.8 mm, round</description>
<wire x1="0" y1="2.921" x2="0" y2="2.667" width="0.0508" layer="21"/>
<wire x1="0" y1="-2.667" x2="0" y2="-2.921" width="0.0508" layer="21"/>
<wire x1="-1.778" y1="0" x2="0" y2="-1.778" width="2.286" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="1.778" x2="1.778" y2="0" width="2.286" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="0.635" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="2.921" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="3.175" width="0.8128" layer="39"/>
<circle x="0" y="0" radius="3.175" width="0.8128" layer="40"/>
<circle x="0" y="0" radius="3.175" width="0.8128" layer="43"/>
<circle x="0" y="0" radius="1.5" width="0.2032" layer="21"/>
<pad name="B2,8" x="0" y="0" drill="2.8" diameter="5.334"/>
</package>
<package name="3,0-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 3.0 mm, round</description>
<wire x1="-2.159" y1="0" x2="0" y2="-2.159" width="2.4892" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.159" x2="2.159" y2="0" width="2.4892" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="3.429" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="39"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="40"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="43"/>
<circle x="0" y="0" radius="1.6" width="0.2032" layer="21"/>
<pad name="B3,0" x="0" y="0" drill="3" diameter="5.842"/>
<text x="-1.27" y="-3.81" size="1.27" layer="48">3,0</text>
</package>
<package name="3,2-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 3.2 mm, round</description>
<wire x1="-2.159" y1="0" x2="0" y2="-2.159" width="2.4892" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.159" x2="2.159" y2="0" width="2.4892" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="3.429" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="3.683" width="1.27" layer="39"/>
<circle x="0" y="0" radius="3.683" width="1.27" layer="40"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="43"/>
<circle x="0" y="0" radius="1.7" width="0.1524" layer="21"/>
<pad name="B3,2" x="0" y="0" drill="3.2" diameter="5.842"/>
<text x="-1.27" y="-3.81" size="1.27" layer="48">3,2</text>
</package>
<package name="3,3-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 3.3 mm, round</description>
<wire x1="-2.159" y1="0" x2="0" y2="-2.159" width="2.4892" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.159" x2="2.159" y2="0" width="2.4892" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="3.429" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="3.683" width="1.27" layer="39"/>
<circle x="0" y="0" radius="3.683" width="1.27" layer="40"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="43"/>
<circle x="0" y="0" radius="1.7" width="0.2032" layer="21"/>
<pad name="B3,3" x="0" y="0" drill="3.3" diameter="5.842"/>
</package>
<package name="3,6-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 3.6 mm, round</description>
<wire x1="-2.159" y1="0" x2="0" y2="-2.159" width="2.4892" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.159" x2="2.159" y2="0" width="2.4892" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="3.429" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="3.683" width="1.397" layer="39"/>
<circle x="0" y="0" radius="3.683" width="1.397" layer="40"/>
<circle x="0" y="0" radius="3.556" width="1.016" layer="43"/>
<circle x="0" y="0" radius="1.9" width="0.2032" layer="21"/>
<pad name="B3,6" x="0" y="0" drill="3.6" diameter="5.842"/>
</package>
<package name="4,1-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 4.1 mm, round</description>
<wire x1="-2.54" y1="0" x2="0" y2="-2.54" width="3.9116" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="3.9116" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="4.572" width="0.1524" layer="21"/>
<circle x="0" y="0" radius="5.08" width="2" layer="43"/>
<circle x="0" y="0" radius="2.15" width="0.2032" layer="21"/>
<pad name="B4,1" x="0" y="0" drill="4.1" diameter="8"/>
</package>
<package name="4,3-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 4.3 mm, round</description>
<wire x1="-2.54" y1="0" x2="0" y2="-2.54" width="3.9116" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="3.9116" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="4.4958" width="0.1524" layer="51"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="5.588" width="2" layer="43"/>
<circle x="0" y="0" radius="5.588" width="2" layer="39"/>
<circle x="0" y="0" radius="5.588" width="2" layer="40"/>
<circle x="0" y="0" radius="2.25" width="0.1524" layer="21"/>
<pad name="B4,3" x="0" y="0" drill="4.3" diameter="9"/>
</package>
<package name="4,5-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 4.5 mm, round</description>
<wire x1="-2.54" y1="0" x2="0" y2="-2.54" width="3.9116" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="3.9116" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="4.4958" width="0.1524" layer="51"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="5.588" width="2" layer="43"/>
<circle x="0" y="0" radius="5.588" width="2" layer="39"/>
<circle x="0" y="0" radius="5.588" width="2" layer="40"/>
<circle x="0" y="0" radius="2.35" width="0.1524" layer="21"/>
<pad name="B4,5" x="0" y="0" drill="4.5" diameter="9"/>
</package>
<package name="5,0-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 5.0 mm, round</description>
<wire x1="-2.54" y1="0" x2="0" y2="-2.54" width="3.9116" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="3.9116" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="4.4958" width="0.1524" layer="51"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="5.588" width="2" layer="43"/>
<circle x="0" y="0" radius="5.588" width="2" layer="39"/>
<circle x="0" y="0" radius="5.588" width="2" layer="40"/>
<circle x="0" y="0" radius="2.6" width="0.1524" layer="21"/>
<pad name="B5" x="0" y="0" drill="5" diameter="9"/>
</package>
<package name="5,5-PAD">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt; 5.5 mm, round</description>
<wire x1="-2.54" y1="0" x2="0" y2="-2.54" width="3.9116" layer="51" curve="90" cap="flat"/>
<wire x1="0" y1="2.54" x2="2.54" y2="0" width="3.9116" layer="51" curve="-90" cap="flat"/>
<circle x="0" y="0" radius="4.4958" width="0.1524" layer="51"/>
<circle x="0" y="0" radius="0.762" width="0.4572" layer="51"/>
<circle x="0" y="0" radius="5.588" width="2" layer="43"/>
<circle x="0" y="0" radius="5.588" width="2" layer="39"/>
<circle x="0" y="0" radius="5.588" width="2" layer="40"/>
<circle x="0" y="0" radius="2.85" width="0.1524" layer="21"/>
<pad name="B5,5" x="0" y="0" drill="5.5" diameter="9"/>
</package>
<package name="CSK_MOUNTING_HOLE">
<description>&lt;h1&gt;Cubesat Kit M/B Mounting Hole&lt;/h1&gt;
&lt;h2&gt;0.125 in. dia., 0.25 in pad.</description>
<pad name="P$1" x="0" y="0" drill="3.175" diameter="6.35" rot="R90"/>
</package>
</packages>
<symbols>
<symbol name="MOUNT-PAD">
<wire x1="0.254" y1="2.032" x2="2.032" y2="0.254" width="1.016" layer="94" curve="-75.749967" cap="flat"/>
<wire x1="-2.032" y1="0.254" x2="-0.254" y2="2.032" width="1.016" layer="94" curve="-75.749967" cap="flat"/>
<wire x1="-2.032" y1="-0.254" x2="-0.254" y2="-2.032" width="1.016" layer="94" curve="75.749967" cap="flat"/>
<wire x1="0.254" y1="-2.032" x2="2.032" y2="-0.254" width="1.016" layer="94" curve="75.749967" cap="flat"/>
<circle x="0" y="0" radius="1.524" width="0.0508" layer="94"/>
<text x="2.794" y="0.5842" size="1.778" layer="95">&gt;NAME</text>
<text x="2.794" y="-2.4638" size="1.778" layer="96">&gt;VALUE</text>
<pin name="MOUNT" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="MOUNT-PAD-ROUND" prefix="H">
<description>&lt;b&gt;MOUNTING PAD&lt;/b&gt;, round</description>
<gates>
<gate name="G$1" symbol="MOUNT-PAD" x="0" y="0"/>
</gates>
<devices>
<device name="2.8" package="2,8-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B2,8"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.0" package="3,0-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B3,0"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.2" package="3,2-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B3,2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.3" package="3,3-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B3,3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="3.6" package="3,6-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B3,6"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="4.1" package="4,1-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B4,1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="4.3" package="4,3-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B4,3"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="4.5" package="4,5-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B4,5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5.0" package="5,0-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="5.5" package="5,5-PAD">
<connects>
<connect gate="G$1" pin="MOUNT" pad="B5,5"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="CSK_MTG_HOLE_A5" package="CSK_MOUNTING_HOLE">
<connects>
<connect gate="G$1" pin="MOUNT" pad="P$1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="supply2">
<description>&lt;b&gt;Supply Symbols&lt;/b&gt;&lt;p&gt;
GND, VCC, 0V, +5V, -5V, etc.&lt;p&gt;
Please keep in mind, that these devices are necessary for the
automatic wiring of the supply signals.&lt;p&gt;
The pin name defined in the symbol is identical to the net which is to be wired automatically.&lt;p&gt;
In this library the device names are the same as the pin names of the symbols, therefore the correct signal names appear next to the supply symbols in the schematic.&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="GND">
<wire x1="-1.27" y1="0" x2="1.27" y2="0" width="0.254" layer="94"/>
<wire x1="1.27" y1="0" x2="0" y2="-1.27" width="0.254" layer="94"/>
<wire x1="0" y1="-1.27" x2="-1.27" y2="0" width="0.254" layer="94"/>
<text x="-1.905" y="-3.175" size="1.778" layer="96">&gt;VALUE</text>
<pin name="GND" x="0" y="2.54" visible="off" length="short" direction="sup" rot="R270"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="GND" prefix="SUPPLY">
<description>&lt;b&gt;SUPPLY SYMBOL&lt;/b&gt;</description>
<gates>
<gate name="GND" symbol="GND" x="0" y="0"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="gwu_mpnl_ucat_v8">
<description>&lt;b&gt;PCB Matrix Packages&lt;/b&gt;&lt;p&gt;</description>
<packages>
<package name="LGA-141-LTC-05-08-1840-B">
<smd name="A1" x="-7.116" y="-10.192" dx="0.63" dy="0.63" layer="1" roundness="50"/>
<smd name="A2" x="-5.846" y="-10.192" dx="0.63" dy="0.63" layer="1"/>
<smd name="A3" x="-4.576" y="-10.192" dx="0.63" dy="0.63" layer="1"/>
<smd name="A4" x="-3.306" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A5" x="-2.036" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A6" x="-0.766" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A7" x="0.504" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A8" x="1.774" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A9" x="3.044" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A10" x="4.314" y="-10.192" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="A11" x="5.584" y="-10.192" dx="0.63" dy="0.63" layer="1"/>
<smd name="A12" x="6.854" y="-10.192" dx="0.63" dy="0.63" layer="1"/>
<smd name="B1" x="-7.116" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B2" x="-5.846" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B3" x="-4.576" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B4" x="-3.306" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B5" x="-2.036" y="-8.922" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="B6" x="-0.766" y="-8.922" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="B7" x="0.504" y="-8.922" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="B8" x="1.774" y="-8.922" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="B9" x="3.044" y="-8.922" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="B10" x="4.314" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B11" x="5.584" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="B12" x="6.854" y="-8.922" dx="0.63" dy="0.63" layer="1"/>
<smd name="C1" x="-7.116" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C2" x="-5.846" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C3" x="-4.576" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C4" x="-3.306" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C5" x="-2.036" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C6" x="-0.766" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C7" x="0.504" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C8" x="1.774" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C9" x="3.044" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C10" x="4.314" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C11" x="5.584" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="C12" x="6.854" y="-7.652" dx="0.63" dy="0.63" layer="1"/>
<smd name="D1" x="-7.116" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D2" x="-5.846" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D3" x="-4.576" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D4" x="-3.306" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D5" x="-2.036" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D6" x="-0.766" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D7" x="0.504" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D8" x="1.774" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D9" x="3.044" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D10" x="4.314" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D11" x="5.584" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="D12" x="6.854" y="-6.382" dx="0.63" dy="0.63" layer="1"/>
<smd name="E1" x="-7.116" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E2" x="-5.846" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E3" x="-4.576" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E4" x="-3.306" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E5" x="-2.036" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E6" x="-0.766" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E7" x="0.504" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E8" x="1.774" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E9" x="3.044" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E10" x="4.314" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E11" x="5.584" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="E12" x="6.854" y="-5.112" dx="0.63" dy="0.63" layer="1"/>
<smd name="F1" x="-7.116" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F2" x="-5.846" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F3" x="-4.576" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F4" x="-3.306" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F5" x="-2.036" y="-3.842" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="F6" x="-0.766" y="-3.842" dx="0.63" dy="0.63" layer="1" stop="no"/>
<smd name="F10" x="4.314" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F11" x="5.584" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="F12" x="6.854" y="-3.842" dx="0.63" dy="0.63" layer="1"/>
<smd name="G1" x="-7.116" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G2" x="-5.846" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G3" x="-4.576" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G4" x="-3.306" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G5" x="-2.036" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G6" x="-0.766" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G7" x="0.504" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G8" x="1.774" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G9" x="3.044" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G10" x="4.314" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G11" x="5.584" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="G12" x="6.854" y="-2.572" dx="0.63" dy="0.63" layer="1"/>
<smd name="VOUT" x="-7.116" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H2" x="-5.846" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H3" x="-4.576" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H4" x="-3.306" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H5" x="-2.036" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H6" x="-0.766" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H7" x="0.504" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H8" x="1.774" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H9" x="3.044" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H10" x="4.314" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H11" x="5.584" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="H12" x="6.854" y="-1.302" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@J1" x="-7.116" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@J2" x="-5.846" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@J3" x="-4.576" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@J4" x="-3.306" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J5" x="-2.036" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J6" x="-0.766" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J7" x="0.504" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J8" x="1.774" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J9" x="3.044" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J10" x="4.314" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J11" x="5.584" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="J12" x="6.854" y="-0.032" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@K1" x="-7.116" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@K2" x="-5.846" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@K3" x="-4.576" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@K4" x="-3.306" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K5" x="-2.036" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K6" x="-0.766" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K7" x="0.504" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K8" x="1.774" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K9" x="3.044" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K10" x="4.314" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K11" x="5.584" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="K12" x="6.854" y="1.238" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@L1" x="-7.116" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@L2" x="-5.846" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@L3" x="-4.576" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@L4" x="-3.306" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L5" x="-2.036" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L6" x="-0.766" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L7" x="0.504" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L8" x="1.774" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L9" x="3.044" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L10" x="4.314" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L11" x="5.584" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="L12" x="6.854" y="2.508" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@M1" x="-7.116" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@M2" x="-5.846" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@M3" x="-4.576" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="SW1@M4" x="-3.306" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M5" x="-2.036" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M6" x="-0.766" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M7" x="0.504" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M8" x="1.774" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M9" x="3.044" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M10" x="4.314" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M11" x="5.584" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<smd name="M12" x="6.854" y="3.778" dx="0.63" dy="0.63" layer="1"/>
<wire x1="-2.7435" y1="4.393" x2="-2.6935" y2="4.393" width="0" layer="21"/>
<wire x1="-2.6935" y1="4.393" x2="-0.131" y2="4.393" width="0" layer="21"/>
<wire x1="-0.131" y1="4.393" x2="7.419" y2="4.393" width="0" layer="21"/>
<wire x1="7.419" y1="-10.757" x2="7.419" y2="-4.507" width="0" layer="21"/>
<wire x1="7.419" y1="-4.507" x2="7.419" y2="4.393" width="0" layer="21"/>
<wire x1="-7.331" y1="-10.757" x2="-3.881" y2="-10.757" width="0" layer="21"/>
<wire x1="-3.881" y1="-10.757" x2="4.969" y2="-10.757" width="0" layer="21"/>
<wire x1="4.969" y1="-10.757" x2="7.419" y2="-10.757" width="0" layer="21"/>
<wire x1="-7.681" y1="-10.457" x2="-7.681" y2="-0.6695" width="0" layer="21"/>
<wire x1="-7.681" y1="-0.6695" x2="-7.681" y2="-0.657" width="0" layer="21"/>
<wire x1="-7.681" y1="-10.457" x2="-7.381" y2="-10.757" width="0" layer="21"/>
<wire x1="-7.681" y1="-0.657" x2="-2.7435" y2="-0.657" width="0" layer="21"/>
<wire x1="-2.7435" y1="-3.207" x2="-2.7435" y2="-0.657" width="0" layer="21"/>
<wire x1="-2.7435" y1="-0.657" x2="-2.7435" y2="4.393" width="0" layer="21"/>
<wire x1="3.669" y1="-0.657" x2="3.669" y2="-0.607" width="0" layer="21" style="shortdash"/>
<wire x1="3.669" y1="-0.607" x2="3.669" y2="4.343" width="0" layer="21"/>
<wire x1="3.669" y1="-0.607" x2="3.669" y2="-0.657" width="0" layer="21" style="longdash"/>
<wire x1="3.669" y1="-0.657" x2="7.369" y2="-0.657" width="0" layer="21" style="longdash"/>
<wire x1="-0.131" y1="4.393" x2="-0.131" y2="0.643" width="0" layer="21" style="longdash"/>
<wire x1="-0.131" y1="0.643" x2="1.119" y2="0.643" width="0" layer="21" style="longdash"/>
<wire x1="1.119" y1="0.643" x2="1.119" y2="-0.657" width="0" layer="21" style="longdash"/>
<wire x1="1.119" y1="-0.657" x2="3.669" y2="-0.657" width="0" layer="21" style="longdash"/>
<wire x1="-7.631" y1="-5.757" x2="-5.231" y2="-5.757" width="0" layer="21" style="longdash"/>
<wire x1="-5.231" y1="-5.757" x2="-5.231" y2="-4.507" width="0" layer="21" style="longdash"/>
<wire x1="-2.7435" y1="-3.207" x2="-0.131" y2="-3.207" width="0" layer="21" style="longdash"/>
<wire x1="-0.131" y1="-3.207" x2="3.669" y2="-3.207" width="0" layer="21" style="longdash"/>
<wire x1="3.669" y1="-3.207" x2="3.669" y2="-4.407" width="0" layer="21" style="longdash"/>
<wire x1="-5.231" y1="-4.507" x2="-2.7435" y2="-4.507" width="0" layer="21" style="longdash"/>
<wire x1="-0.131" y1="-4.507" x2="7.419" y2="-4.507" width="0" layer="21" style="longdash"/>
<wire x1="-3.881" y1="-10.757" x2="-3.931" y2="-10.757" width="0.127" layer="21" style="longdash"/>
<wire x1="-3.931" y1="-10.757" x2="-3.931" y2="-9.557" width="0" layer="21" style="longdash"/>
<wire x1="-3.931" y1="-9.557" x2="-2.681" y2="-9.557" width="0" layer="21" style="longdash"/>
<wire x1="-2.681" y1="-9.557" x2="-2.681" y2="-8.307" width="0" layer="21" style="longdash"/>
<wire x1="-2.681" y1="-8.307" x2="3.669" y2="-8.307" width="0" layer="21" style="longdash"/>
<wire x1="3.669" y1="-8.307" x2="3.669" y2="-9.557" width="0" layer="21" style="longdash"/>
<wire x1="3.669" y1="-9.557" x2="4.969" y2="-9.557" width="0" layer="21" style="longdash"/>
<wire x1="4.969" y1="-9.557" x2="4.969" y2="-10.757" width="0" layer="21" style="longdash"/>
<text x="-7.381" y="-11.357" size="0.4064" layer="21">1</text>
<text x="-8.131" y="-10.357" size="0.4064" layer="21">A</text>
<text x="6.669" y="4.743" size="0.4064" layer="21">12</text>
<text x="7.719" y="3.693" size="0.4064" layer="21">M</text>
<text x="0.069" y="4.693" size="0.8128" layer="21">SW2</text>
<text x="8.469" y="0.893" size="0.8128" layer="21" rot="R90">VIN</text>
<text x="7.819" y="-1.807" size="0.3048" layer="21" rot="R270">RSENSE</text>
<text x="-8.281" y="-9.657" size="0.8128" layer="21" rot="R90">PGND</text>
<text x="-8.341" y="-4.587" size="0.8128" layer="21" rot="SR90">VOUT</text>
<text x="-8.441" y="0.573" size="0.8128" layer="21" rot="R90">SW1</text>
<text x="-3.681" y="-12.557" size="1.27" layer="25">&gt;NAME</text>
<wire x1="-2.7435" y1="-3.207" x2="-2.7435" y2="-4.507" width="0" layer="21" style="longdash"/>
<wire x1="-2.7435" y1="-4.507" x2="-0.131" y2="-4.507" width="0" layer="21" style="longdash"/>
<wire x1="-0.131" y1="-4.507" x2="-0.131" y2="-3.207" width="0" layer="21" style="longdash"/>
<wire x1="-2.6935" y1="4.393" x2="-7.681" y2="4.393" width="0" layer="21" style="longdash"/>
<wire x1="-7.681" y1="4.393" x2="-7.681" y2="-0.6695" width="0" layer="21" style="longdash"/>
<text x="8.619" y="-9.457" size="0.8128" layer="21" rot="R90">PGND</text>
<wire x1="-15.72" y1="-14.41" x2="15.207" y2="-14.41" width="0" layer="21" style="longdash"/>
<wire x1="15.207" y1="-14.41" x2="15.207" y2="19.24" width="0" layer="21" style="longdash"/>
<wire x1="15.207" y1="19.24" x2="-15.72" y2="19.24" width="0" layer="21" style="longdash"/>
<wire x1="-15.72" y1="19.24" x2="-15.72" y2="-14.41" width="0" layer="21" style="longdash"/>
</package>
<package name="MSS1048">
<wire x1="1" y1="0" x2="8.5857875" y2="0" width="0.127" layer="21"/>
<wire x1="8.5857875" y1="0" x2="10" y2="1.4142125" width="0.127" layer="21" curve="90"/>
<wire x1="10" y1="1.4142125" x2="10" y2="9" width="0.127" layer="21"/>
<wire x1="10" y1="9" x2="9.979346875" y2="9" width="0.127" layer="21"/>
<wire x1="9.979346875" y1="9" x2="8.779346875" y2="10.2" width="0.127" layer="21"/>
<wire x1="8.779346875" y1="10.2" x2="1.562046875" y2="10.2" width="0.127" layer="21"/>
<wire x1="0" y1="8.637953125" x2="0" y2="1" width="0.127" layer="21"/>
<wire x1="0" y1="1" x2="1" y2="0" width="0.127" layer="21"/>
<wire x1="1.5" y1="10.25" x2="0" y2="8.75" width="0.127" layer="21"/>
<smd name="1" x="5" y="9.85" dx="1.78" dy="3.56" layer="1" rot="R90"/>
<smd name="2" x="5" y="0.35" dx="1.78" dy="3.56" layer="1" rot="R90"/>
<text x="1.27" y="5.08" size="1.27" layer="25">&gt;NAME</text>
</package>
<package name="CSK-BUS-PKG">
<description>&lt;h1&gt;Cubesat Kit Bus Connector&lt;/h1&gt;&lt;h2&gt;Spec A5&lt;/h2&gt;Samtech ESQ Series, or compatible ELEVATED SOCKET, .100 inch(2.54mm) PITCH x 2 Pcs</description>
<pad name="1" x="-29.21" y="-3.81" drill="1.016" diameter="1.524" shape="square"/>
<pad name="2" x="-29.21" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="3" x="-26.67" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="4" x="-26.67" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="5" x="-24.13" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="6" x="-24.13" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="7" x="-21.59" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="8" x="-21.59" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="9" x="-19.05" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="10" x="-19.05" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="11" x="-16.51" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="12" x="-16.51" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="13" x="-13.97" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="14" x="-13.97" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="15" x="-11.43" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="16" x="-11.43" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="17" x="-8.89" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="18" x="-8.89" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="19" x="-6.35" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="20" x="-6.35" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="21" x="-3.81" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="22" x="-3.81" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="23" x="-1.27" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="24" x="-1.27" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="25" x="1.27" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="26" x="1.27" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="27" x="3.81" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="28" x="3.81" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="29" x="6.35" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="30" x="6.35" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="31" x="8.89" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="32" x="8.89" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="33" x="11.43" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="34" x="11.43" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="35" x="13.97" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="36" x="13.97" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="37" x="16.51" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="38" x="16.51" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="39" x="19.05" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="40" x="19.05" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="41" x="21.59" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="42" x="21.59" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="43" x="24.13" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="44" x="24.13" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="45" x="26.67" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="46" x="26.67" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="47" x="29.21" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="48" x="29.21" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="49" x="31.75" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="50" x="31.75" y="-1.27" drill="1.016" diameter="1.524"/>
<pad name="51" x="34.29" y="-3.81" drill="1.016" diameter="1.524"/>
<pad name="52" x="34.29" y="-1.27" drill="1.016" diameter="1.524"/>
<wire x1="-30.734" y1="-5.016" x2="-30.734" y2="-0.064" width="0.254" layer="51"/>
<wire x1="-30.734" y1="-0.064" x2="35.814" y2="-0.064" width="0.254" layer="51"/>
<wire x1="35.814" y1="-0.064" x2="35.814" y2="-5.016" width="0.254" layer="51"/>
<wire x1="35.814" y1="-5.016" x2="-30.734" y2="-5.016" width="0.254" layer="51"/>
<pad name="53" x="-29.21" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="54" x="-29.21" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="55" x="-26.67" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="56" x="-26.67" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="57" x="-24.13" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="58" x="-24.13" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="59" x="-21.59" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="60" x="-21.59" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="61" x="-19.05" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="62" x="-19.05" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="63" x="-16.51" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="64" x="-16.51" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="65" x="-13.97" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="66" x="-13.97" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="67" x="-11.43" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="68" x="-11.43" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="69" x="-8.89" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="70" x="-8.89" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="71" x="-6.35" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="72" x="-6.35" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="73" x="-3.81" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="74" x="-3.81" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="75" x="-1.27" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="76" x="-1.27" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="77" x="1.27" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="78" x="1.27" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="79" x="3.81" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="80" x="3.81" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="81" x="6.35" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="82" x="6.35" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="83" x="8.89" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="84" x="8.89" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="85" x="11.43" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="86" x="11.43" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="87" x="13.97" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="88" x="13.97" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="89" x="16.51" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="90" x="16.51" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="91" x="19.05" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="92" x="19.05" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="93" x="21.59" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="94" x="21.59" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="95" x="24.13" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="96" x="24.13" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="97" x="26.67" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="98" x="26.67" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="99" x="29.21" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="100" x="29.21" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="101" x="31.75" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="102" x="31.75" y="3.81" drill="1.016" diameter="1.524"/>
<pad name="103" x="34.29" y="1.27" drill="1.016" diameter="1.524"/>
<pad name="104" x="34.29" y="3.81" drill="1.016" diameter="1.524"/>
<wire x1="-30.734" y1="0.064" x2="-30.734" y2="5.016" width="0.254" layer="51"/>
<wire x1="-30.734" y1="5.016" x2="35.814" y2="5.016" width="0.254" layer="51"/>
<wire x1="35.814" y1="5.016" x2="35.814" y2="0.064" width="0.254" layer="51"/>
<wire x1="35.814" y1="0.064" x2="-30.734" y2="0.064" width="0.254" layer="51"/>
<text x="-33.02" y="-5.08" size="1.27" layer="21">1</text>
<text x="-33.02" y="0.635" size="1.27" layer="21">53</text>
<text x="-5.08" y="-7.62" size="1.27" layer="21">CubeSat Kit Bus</text>
</package>
<package name="MOLEX-MINI-PCI-EXPRESS-8MM-52CKT">
<smd name="1" x="-11.65" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="3" x="-10.85" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="5" x="-10.05" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="7" x="-9.25" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="9" x="-8.45" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="11" x="-7.65" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="13" x="-6.85" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="15" x="-6.05" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="17" x="-2.05" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="19" x="-1.25" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="21" x="-0.45" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="23" x="0.35" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="25" x="1.15" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="27" x="1.95" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="29" x="2.75" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="31" x="3.55" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="33" x="4.35" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="35" x="5.15" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="37" x="5.95" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="39" x="6.75" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="41" x="7.55" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="43" x="8.35" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="45" x="9.15" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="47" x="9.95" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="49" x="10.75" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="51" x="11.55" y="-26.8" dx="0.6" dy="2" layer="1"/>
<smd name="2" x="-11.2475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="4" x="-10.4475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="6" x="-9.6475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="8" x="-8.8475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="10" x="-8.0475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="12" x="-7.2475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="14" x="-6.4475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="16" x="-5.6475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="18" x="-1.6475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="20" x="-0.8475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="22" x="-0.0475" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="24" x="0.7525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="26" x="1.5525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="28" x="2.3525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="30" x="3.1525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="32" x="3.9525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="34" x="4.7525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="36" x="5.5525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="38" x="6.3525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="40" x="7.1525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="42" x="7.9525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="44" x="8.7525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="46" x="9.5525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="48" x="10.3525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="50" x="11.1525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<smd name="52" x="11.9525" y="-18.576" dx="0.6" dy="2" layer="1"/>
<hole x="-12.35" y="-22.7" drill="1.6"/>
<hole x="12.65" y="-22.7" drill="1.1"/>
<smd name="P$1" x="-14.5" y="-26.2" dx="2.3" dy="3.2" layer="1"/>
<smd name="P$2" x="14.8" y="-26.2" dx="2.3" dy="3.2" layer="1"/>
<hole x="-11.95" y="27.7" drill="1.6"/>
<hole x="12.25" y="27.7" drill="1.1"/>
<smd name="P$3" x="12.25" y="24.6" dx="4.8" dy="3" layer="1" rot="R180"/>
<smd name="P$4" x="-11.95" y="24.6" dx="4.8" dy="3" layer="1"/>
<smd name="P$5" x="-11.95" y="30.8" dx="4.8" dy="3" layer="1"/>
<smd name="P$6" x="12.25" y="30.8" dx="4.8" dy="3" layer="1"/>
<wire x1="-9.3" y1="22.9" x2="-9.3" y2="26.3" width="0.127" layer="39"/>
<wire x1="-9.3" y1="32.6" x2="-14.65" y2="32.6" width="0.127" layer="39"/>
<wire x1="9.65" y1="22.9" x2="14.85" y2="22.9" width="0.127" layer="39"/>
<wire x1="14.85" y1="32.55" x2="9.7" y2="32.55" width="0.127" layer="39"/>
<wire x1="-15.85" y1="-24.4" x2="-15.85" y2="-28" width="0.127" layer="39"/>
<wire x1="-15.85" y1="-28" x2="-13.15" y2="-28" width="0.127" layer="39"/>
<wire x1="-13.15" y1="-28" x2="-13.15" y2="-24.4" width="0.127" layer="39"/>
<wire x1="-13.15" y1="-24.4" x2="-15.85" y2="-24.4" width="0.127" layer="39"/>
<wire x1="13.45" y1="-24.45" x2="13.45" y2="-28" width="0.127" layer="39"/>
<wire x1="13.45" y1="-28" x2="16.1" y2="-28" width="0.127" layer="39"/>
<wire x1="16.15" y1="-28" x2="16.15" y2="-24.4" width="0.127" layer="39"/>
<wire x1="16.15" y1="-24.4" x2="13.45" y2="-24.4" width="0.127" layer="39"/>
<wire x1="-14.6" y1="29.1" x2="-9.3" y2="29.1" width="0.127" layer="39"/>
<wire x1="-14.6" y1="26.3" x2="-9.3" y2="26.3" width="0.127" layer="39"/>
<wire x1="9.65" y1="29.1" x2="14.85" y2="29.1" width="0.127" layer="39"/>
<wire x1="9.65" y1="26.35" x2="14.85" y2="26.35" width="0.127" layer="39"/>
<wire x1="-14.65" y1="32.6" x2="-14.65" y2="29.1" width="0.127" layer="39"/>
<wire x1="-9.3" y1="32.6" x2="-9.3" y2="29.1" width="0.127" layer="39"/>
<wire x1="-14.55" y1="26.25" x2="-14.55" y2="22.9" width="0.127" layer="39"/>
<wire x1="-14.55" y1="22.9" x2="-9.3" y2="22.9" width="0.127" layer="39"/>
<wire x1="9.65" y1="32.5" x2="9.65" y2="29.1" width="0.127" layer="39"/>
<wire x1="14.85" y1="32.55" x2="14.85" y2="29.15" width="0.127" layer="39"/>
<wire x1="14.85" y1="26.35" x2="14.85" y2="22.9" width="0.127" layer="39"/>
<wire x1="9.65" y1="26.35" x2="9.65" y2="22.9" width="0.127" layer="39"/>
<wire x1="-17.78" y1="-30.48" x2="17.78" y2="-30.48" width="0.127" layer="21"/>
<wire x1="17.78" y1="-30.48" x2="17.78" y2="34.29" width="0.127" layer="21"/>
<wire x1="17.78" y1="34.29" x2="-17.78" y2="34.29" width="0.127" layer="21"/>
<wire x1="-17.78" y1="34.29" x2="-17.78" y2="-30.48" width="0.127" layer="21"/>
<text x="-12.065" y="-25.4" size="0.3048" layer="21">1</text>
<text x="-11.43" y="-17.145" size="0.3048" layer="21">2</text>
<text x="12.7" y="-17.145" size="0.3048" layer="21">52</text>
<text x="5.08" y="-12.7" size="1.27" layer="21" rot="R90">MINI-PCI EXPRESS CONN W/LATCH 
FOR NETBURNER NANO55415 CU MODULE

REF
MOLEX SD-67910-001
MOLEX SD-48099-400</text>
</package>
<package name="OS-CON-SVPF-F12">
<circle x="0" y="0" radius="5" width="0.127" layer="21"/>
<wire x1="-5.2" y1="5.2" x2="-5.2" y2="-3.644365625" width="0.127" layer="21"/>
<wire x1="-5.2" y1="-3.644365625" x2="-3.644365625" y2="-5.2" width="0.127" layer="21"/>
<wire x1="-3.644365625" y1="-5.2" x2="3.71339375" y2="-5.2" width="0.127" layer="21"/>
<wire x1="3.71339375" y1="-5.2" x2="5.2" y2="-3.71339375" width="0.127" layer="21"/>
<wire x1="5.2" y1="-3.71339375" x2="5.2" y2="5.2" width="0.127" layer="21"/>
<wire x1="5.2" y1="5.2" x2="-5.2" y2="5.2" width="0.4064" layer="21"/>
<text x="-2.5" y="0.3" size="1.016" layer="25">&gt;NAME</text>
<smd name="A1" x="0" y="-4.3" dx="4.4" dy="1.9" layer="1" rot="R90"/>
<smd name="K1" x="0" y="4.4" dx="4.4" dy="1.9" layer="1" roundness="20" rot="R90"/>
</package>
<package name="MLCC-X7R-1210">
<wire x1="-1.5" y1="-1.2" x2="1.2" y2="-1.2" width="0.1" layer="21"/>
<wire x1="1.2" y1="-1.2" x2="1.7" y2="-1.2" width="0.1" layer="21"/>
<wire x1="1.7" y1="-1.2" x2="1.7" y2="1.3" width="0.1" layer="21"/>
<wire x1="1.7" y1="1.3" x2="1.2" y2="1.3" width="0.1" layer="21"/>
<wire x1="1.2" y1="1.3" x2="-1" y2="1.3" width="0.1" layer="21"/>
<wire x1="-1" y1="1.3" x2="-1.5" y2="1.3" width="0.1" layer="21"/>
<wire x1="-1.5" y1="1.3" x2="-1.5" y2="-1.2" width="0.1" layer="21"/>
<wire x1="-1" y1="-1.1" x2="-1" y2="1.3" width="0.1" layer="21"/>
<wire x1="1.2" y1="-1.2" x2="1.2" y2="1.3" width="0.1" layer="21"/>
<smd name="1" x="1.6" y="0.05" dx="1" dy="2.8" layer="1" roundness="20"/>
<smd name="2" x="-1.35" y="0.05" dx="1" dy="2.8" layer="1"/>
<text x="-1.95" y="1.85" size="1.27" layer="25">&gt;NAME</text>
</package>
</packages>
<symbols>
<symbol name="LTM4609.SCH">
<pin name="EXTV_CC" x="-22.86" y="25.4" length="middle"/>
<pin name="INTV_CC" x="-22.86" y="20.32" length="middle"/>
<pin name="PGOOD" x="-22.86" y="15.24" length="middle"/>
<pin name="RUN" x="-22.86" y="10.16" length="middle"/>
<pin name="STBYMD" x="-22.86" y="5.08" length="middle"/>
<pin name="COMP" x="-22.86" y="0" length="middle"/>
<pin name="SS" x="-22.86" y="-5.08" length="middle"/>
<pin name="PLLIN" x="-22.86" y="-10.16" length="middle"/>
<pin name="PLLFLTR" x="-22.86" y="-15.24" length="middle"/>
<pin name="FCB" x="-22.86" y="-20.32" length="middle"/>
<pin name="SGND" x="-22.86" y="-25.4" length="middle"/>
<pin name="V_IN" x="27.94" y="25.4" length="middle" rot="R180"/>
<pin name="SW2" x="27.94" y="20.32" length="middle" rot="R180"/>
<pin name="SW1" x="27.94" y="10.16" length="middle" rot="R180"/>
<pin name="V_OUT" x="27.94" y="5.08" length="middle" rot="R180"/>
<pin name="V_FB" x="27.94" y="-2.54" length="middle" rot="R180"/>
<pin name="R_SENSE" x="27.94" y="-7.62" length="middle" rot="R180"/>
<pin name="SENSE+" x="27.94" y="-12.7" length="middle" rot="R180"/>
<pin name="SENSE-" x="27.94" y="-20.32" length="middle" rot="R180"/>
<pin name="PGND" x="27.94" y="-25.4" length="middle" rot="R180"/>
<wire x1="-17.78" y1="27.94" x2="-17.78" y2="-27.94" width="0.254" layer="94"/>
<wire x1="-17.78" y1="-27.94" x2="22.86" y2="-27.94" width="0.254" layer="94"/>
<wire x1="22.86" y1="-27.94" x2="22.86" y2="27.94" width="0.254" layer="94"/>
<wire x1="22.86" y1="27.94" x2="-17.78" y2="27.94" width="0.254" layer="94"/>
<text x="-12.7" y="35.56" size="1.778" layer="95">&gt;NAME</text>
<text x="-12.7" y="30.48" size="1.778" layer="96">&gt;VALUE</text>
</symbol>
<symbol name="SHIELDED-POWER-INDUCTOR">
<wire x1="-10.16" y1="0" x2="10.16" y2="0" width="0.254" layer="94"/>
<wire x1="10.16" y1="0" x2="10.16" y2="-10.16" width="0.254" layer="94"/>
<wire x1="10.16" y1="-10.16" x2="-10.16" y2="-10.16" width="0.254" layer="94"/>
<wire x1="-10.16" y1="0" x2="-10.16" y2="-10.16" width="0.254" layer="94"/>
<text x="12.7" y="-2.54" size="1.27" layer="95">&gt;NAME</text>
<text x="12.7" y="-5.08" size="1.27" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="-15.24" length="middle" rot="R90"/>
<pin name="2" x="5.08" y="-15.24" length="middle" rot="R90"/>
<text x="-5.08" y="-5.08" size="1.27" layer="94">Shielded Power
Inductor</text>
</symbol>
<symbol name="CUBESAT-KIT-BUS-A5">
<pin name="P6.3" x="-22.86" y="-12.7" visible="pin" length="middle"/>
<pin name="P6.1" x="-22.86" y="-15.24" length="middle"/>
<pin name="P1.7" x="-22.86" y="-17.78" visible="pin" length="middle"/>
<pin name="P1.5" x="-22.86" y="-20.32" visible="pin" length="middle"/>
<pin name="P1.3" x="-22.86" y="-22.86" visible="pin" length="middle"/>
<pin name="P1.1" x="-22.86" y="-25.4" visible="pin" length="middle"/>
<pin name="P2.7" x="-22.86" y="-27.94" visible="pin" length="middle"/>
<pin name="P2.5" x="-22.86" y="-30.48" visible="pin" length="middle"/>
<pin name="P2.3" x="-22.86" y="-33.02" visible="pin" length="middle"/>
<pin name="P2.1" x="-22.86" y="-35.56" visible="pin" length="middle"/>
<pin name="+5V_SYS@1" x="-22.86" y="-38.1" visible="pin" length="middle"/>
<pin name="VCC_SYS@1" x="-22.86" y="-40.64" visible="pin" length="middle"/>
<pin name="GND@1" x="-22.86" y="-43.18" visible="pin" length="middle"/>
<pin name="GND@3" x="-22.86" y="-45.72" visible="pin" length="middle"/>
<pin name="SW0@1" x="-22.86" y="-48.26" visible="pin" length="middle"/>
<pin name="SW1@1" x="-22.86" y="-50.8" visible="pin" length="middle"/>
<pin name="SW2@1" x="-22.86" y="-53.34" visible="pin" length="middle"/>
<pin name="SW3@1" x="-22.86" y="-55.88" visible="pin" length="middle"/>
<pin name="SW4@1" x="-22.86" y="-58.42" visible="pin" length="middle"/>
<pin name="SW5@1" x="-22.86" y="-60.96" visible="pin" length="middle"/>
<pin name="VBATT@1" x="-22.86" y="-63.5" visible="pin" length="middle"/>
<pin name="USER6" x="-22.86" y="-66.04" visible="pin" length="middle"/>
<pin name="USER8" x="-22.86" y="-68.58" length="middle"/>
<pin name="USER10" x="-22.86" y="-71.12" length="middle"/>
<pin name="P6.2" x="22.86" y="-12.7" visible="pin" length="middle" rot="R180"/>
<pin name="P6.0" x="22.86" y="-15.24" visible="pin" length="middle" rot="R180"/>
<pin name="P1.6" x="22.86" y="-17.78" visible="pin" length="middle" rot="R180"/>
<pin name="P1.4" x="22.86" y="-20.32" visible="pin" length="middle" rot="R180"/>
<pin name="P1.2" x="22.86" y="-22.86" visible="pin" length="middle" rot="R180"/>
<pin name="P1.0" x="22.86" y="-25.4" visible="pin" length="middle" rot="R180"/>
<pin name="P2.6" x="22.86" y="-27.94" visible="pin" length="middle" rot="R180"/>
<pin name="P2.4" x="22.86" y="-30.48" visible="pin" length="middle" rot="R180"/>
<pin name="P2.2" x="22.86" y="-33.02" visible="pin" length="middle" rot="R180"/>
<pin name="P2.0" x="22.86" y="-35.56" visible="pin" length="middle" rot="R180"/>
<pin name="+5V_SYS@2" x="22.86" y="-38.1" visible="pin" length="middle" rot="R180"/>
<pin name="VCC_SYS@2" x="22.86" y="-40.64" length="middle" rot="R180"/>
<pin name="GND@2" x="22.86" y="-43.18" visible="pin" length="middle" rot="R180"/>
<pin name="GND@4" x="22.86" y="-45.72" visible="pin" length="middle" rot="R180"/>
<pin name="SW0@2" x="22.86" y="-48.26" visible="pin" length="middle" rot="R180"/>
<pin name="SW1@2" x="22.86" y="-50.8" visible="pin" length="middle" rot="R180"/>
<pin name="SW2@2" x="22.86" y="-53.34" visible="pin" length="middle" rot="R180"/>
<pin name="SW3@2" x="22.86" y="-55.88" visible="pin" length="middle" rot="R180"/>
<pin name="SW4@2" x="22.86" y="-58.42" visible="pin" length="middle" rot="R180"/>
<pin name="SW5@2" x="22.86" y="-60.96" visible="pin" length="middle" rot="R180"/>
<pin name="VBATT@2" x="22.86" y="-63.5" length="middle" rot="R180"/>
<pin name="USER7" x="22.86" y="-66.04" visible="pin" length="middle" rot="R180"/>
<pin name="USER9" x="22.86" y="-68.58" visible="pin" length="middle" rot="R180"/>
<pin name="USER11" x="22.86" y="-71.12" length="middle" rot="R180"/>
<pin name="P6.6" x="22.86" y="-7.62" visible="pin" length="middle" rot="R180"/>
<pin name="P6.4" x="22.86" y="-10.16" visible="pin" length="middle" rot="R180"/>
<pin name="P6.7" x="-22.86" y="-7.62" visible="pin" length="middle"/>
<pin name="P6.5" x="-22.86" y="-10.16" visible="pin" length="middle"/>
<wire x1="17.78" y1="-73.66" x2="-17.78" y2="-73.66" width="0.254" layer="94"/>
<text x="-7.62" y="-15.24" size="1.778" layer="94">CONN H2/H6
(OUTBOARD)
H-2X26-F </text>
<pin name="P5.3" x="-22.86" y="66.04" visible="pin" length="middle"/>
<pin name="P5.1" x="-22.86" y="63.5" length="middle"/>
<pin name="P4.7" x="-22.86" y="60.96" visible="pin" length="middle"/>
<pin name="P4.5" x="-22.86" y="58.42" visible="pin" length="middle"/>
<pin name="P4.3" x="-22.86" y="55.88" visible="pin" length="middle"/>
<pin name="P4.1" x="-22.86" y="53.34" visible="pin" length="middle"/>
<pin name="P3.7" x="-22.86" y="50.8" visible="pin" length="middle"/>
<pin name="P3.5" x="-22.86" y="48.26" visible="pin" length="middle"/>
<pin name="P3.3" x="-22.86" y="45.72" visible="pin" length="middle"/>
<pin name="P3.1" x="-22.86" y="43.18" visible="pin" length="middle"/>
<pin name="-FAULT" x="-22.86" y="40.64" visible="pin" length="middle"/>
<pin name="SENSE" x="-22.86" y="38.1" visible="pin" length="middle"/>
<pin name="-RESET" x="-22.86" y="35.56" visible="pin" length="middle"/>
<pin name="OFF_VCC" x="-22.86" y="33.02" visible="pin" length="middle"/>
<pin name="+5V_SW" x="-22.86" y="30.48" visible="pin" length="middle"/>
<pin name="-CTS_MHX" x="-22.86" y="27.94" visible="pin" length="middle"/>
<pin name="-DSR_MHX" x="-22.86" y="25.4" visible="pin" length="middle"/>
<pin name="TXD_MHX" x="-22.86" y="22.86" visible="pin" length="middle"/>
<pin name="SDA_SYS" x="-22.86" y="20.32" visible="pin" length="middle"/>
<pin name="SCL_SYS" x="-22.86" y="17.78" visible="pin" length="middle"/>
<pin name="RSVD1" x="-22.86" y="15.24" visible="pin" length="middle"/>
<pin name="USER0" x="-22.86" y="12.7" visible="pin" length="middle"/>
<pin name="USER2" x="-22.86" y="10.16" length="middle"/>
<pin name="USER4" x="-22.86" y="7.62" length="middle"/>
<pin name="P5.2" x="22.86" y="66.04" visible="pin" length="middle" rot="R180"/>
<pin name="P5.0" x="22.86" y="63.5" visible="pin" length="middle" rot="R180"/>
<pin name="P4.6" x="22.86" y="60.96" visible="pin" length="middle" rot="R180"/>
<pin name="P4.4" x="22.86" y="58.42" visible="pin" length="middle" rot="R180"/>
<pin name="P4.2" x="22.86" y="55.88" visible="pin" length="middle" rot="R180"/>
<pin name="P4.0" x="22.86" y="53.34" visible="pin" length="middle" rot="R180"/>
<pin name="P3.6" x="22.86" y="50.8" visible="pin" length="middle" rot="R180"/>
<pin name="P3.4" x="22.86" y="48.26" visible="pin" length="middle" rot="R180"/>
<pin name="P3.2" x="22.86" y="45.72" visible="pin" length="middle" rot="R180"/>
<pin name="P3.0" x="22.86" y="43.18" visible="pin" length="middle" rot="R180"/>
<pin name="VREF+" x="22.86" y="40.64" visible="pin" length="middle" rot="R180"/>
<pin name="VEREF+" x="22.86" y="38.1" length="middle" rot="R180"/>
<pin name="VREF-" x="22.86" y="35.56" visible="pin" length="middle" rot="R180"/>
<pin name="+5V_USB" x="22.86" y="33.02" visible="pin" length="middle" rot="R180"/>
<pin name="-RST_MHX" x="22.86" y="30.48" visible="pin" length="middle" rot="R180"/>
<pin name="-RTS_MHX" x="22.86" y="27.94" visible="pin" length="middle" rot="R180"/>
<pin name="-DTR_MHX" x="22.86" y="25.4" visible="pin" length="middle" rot="R180"/>
<pin name="RXD_MHX" x="22.86" y="22.86" visible="pin" length="middle" rot="R180"/>
<pin name="VBACKUP" x="22.86" y="20.32" visible="pin" length="middle" rot="R180"/>
<pin name="RSVD0" x="22.86" y="17.78" visible="pin" length="middle" rot="R180"/>
<pin name="RSVD2" x="22.86" y="15.24" visible="pin" length="middle" rot="R180"/>
<pin name="USER1" x="22.86" y="12.7" visible="pin" length="middle" rot="R180"/>
<pin name="USER3" x="22.86" y="10.16" visible="pin" length="middle" rot="R180"/>
<pin name="USER5" x="22.86" y="7.62" length="middle" rot="R180"/>
<pin name="P5.6" x="22.86" y="71.12" visible="pin" length="middle" rot="R180"/>
<pin name="P5.4" x="22.86" y="68.58" visible="pin" length="middle" rot="R180"/>
<pin name="P5.7" x="-22.86" y="71.12" visible="pin" length="middle"/>
<pin name="P5.5" x="-22.86" y="68.58" visible="pin" length="middle"/>
<wire x1="-17.78" y1="73.66" x2="17.78" y2="73.66" width="0.254" layer="94"/>
<text x="-7.62" y="63.5" size="1.778" layer="94">CONN H1/H5
(INBOARD)
H-2X26-F</text>
<text x="-12.7" y="88.9" size="5.08" layer="95" rot="R180" align="bottom-right">&gt;NAME</text>
<rectangle x1="-17.78" y1="71.12" x2="-15.24" y2="73.66" layer="94" rot="R270"/>
<text x="-12.7" y="81.28" size="5.08" layer="96" rot="R180" align="bottom-right">&gt;VALUE</text>
<text x="-20.32" y="73.66" size="2.54" layer="94">1</text>
<text x="20.32" y="73.66" size="2.54" layer="94">2</text>
<text x="20.32" y="2.54" size="2.54" layer="94">54</text>
<text x="20.32" y="-76.2" size="2.54" layer="94">104</text>
<text x="-22.86" y="-5.08" size="2.54" layer="94">55</text>
<text x="-22.86" y="2.54" size="2.54" layer="94">53</text>
<wire x1="-17.78" y1="-73.66" x2="-17.78" y2="0" width="0.254" layer="94"/>
<wire x1="-17.78" y1="0" x2="-17.78" y2="73.66" width="0.254" layer="94"/>
<wire x1="17.78" y1="73.66" x2="17.78" y2="0" width="0.254" layer="94"/>
<wire x1="17.78" y1="0" x2="17.78" y2="-73.66" width="0.254" layer="94"/>
<text x="-7.62" y="-2.54" size="1.778" layer="94">Pumpkin
CubeSatKit
Bus Spec A5</text>
</symbol>
<symbol name="UCAT-4CU-B-CONTROL-UNIT-DAUGHTERBOARD">
<pin name="ADC_IN1" x="-27.94" y="-35.56" length="middle"/>
<pin name="ADC_IN0" x="25.4" y="-35.56" length="middle" rot="R180"/>
<pin name="ADC_IN3" x="-27.94" y="-33.02" length="middle"/>
<pin name="ADC_IN2" x="25.4" y="-33.02" length="middle" rot="R180"/>
<pin name="ADC_IN7" x="-27.94" y="-30.48" length="middle"/>
<pin name="ADC_IN4" x="25.4" y="-30.48" length="middle" rot="R180"/>
<pin name="VDDA_DAC_ADC" x="-27.94" y="-27.94" length="middle"/>
<pin name="AGND" x="25.4" y="-27.94" length="middle" rot="R180"/>
<pin name="IRQ7" x="-27.94" y="-25.4" length="middle"/>
<pin name="UART2_CTS" x="25.4" y="-25.4" length="middle" rot="R180"/>
<pin name="RSTI" x="-27.94" y="-22.86" length="middle"/>
<pin name="OW_DAT" x="25.4" y="-22.86" length="middle" rot="R180"/>
<pin name="UART2_RX" x="-27.94" y="-20.32" length="middle"/>
<pin name="UART2_RTS" x="25.4" y="-20.32" length="middle" rot="R180"/>
<pin name="SDHC_DAT3" x="-27.94" y="-17.78" length="middle"/>
<pin name="UART2_TX" x="25.4" y="-17.78" length="middle" rot="R180"/>
<pin name="VCC3V@1" x="-27.94" y="-12.7" length="middle"/>
<pin name="GND@1" x="25.4" y="-12.7" length="middle" rot="R180"/>
<pin name="T0IN" x="-27.94" y="-10.16" length="middle"/>
<pin name="CAN1_RX" x="25.4" y="-10.16" length="middle" rot="R180"/>
<pin name="T2IN" x="-27.94" y="-5.08" length="middle"/>
<pin name="CAN1_TX" x="25.4" y="-7.62" length="middle" rot="R180"/>
<pin name="T3IN" x="-27.94" y="-2.54" length="middle"/>
<pin name="UART0_RX" x="25.4" y="-5.08" length="middle" rot="R180"/>
<pin name="I2C0_SCL" x="-27.94" y="0" length="middle"/>
<pin name="UART0_TX" x="25.4" y="-2.54" length="middle" rot="R180"/>
<pin name="I2C0_SDA" x="-27.94" y="2.54" length="middle"/>
<pin name="UART0_RTS" x="25.4" y="0" length="middle" rot="R180"/>
<pin name="SDHC_CLK" x="-27.94" y="5.08" length="middle"/>
<pin name="UART0_CTS" x="25.4" y="2.54" length="middle" rot="R180"/>
<pin name="SDHC_CMD" x="-27.94" y="7.62" length="middle"/>
<pin name="UART1_RX" x="25.4" y="5.08" length="middle" rot="R180"/>
<pin name="SDHC_DAT0" x="-27.94" y="10.16" length="middle"/>
<pin name="UART1_TX" x="25.4" y="7.62" length="middle" rot="R180"/>
<pin name="SDHC_DAT1" x="-27.94" y="12.7" length="middle"/>
<pin name="UART1_RTS" x="25.4" y="10.16" length="middle" rot="R180"/>
<pin name="SDHC_DAT2" x="-27.94" y="15.24" length="middle"/>
<pin name="UART1_CTS" x="25.4" y="12.7" length="middle" rot="R180"/>
<pin name="VCC3VE" x="-27.94" y="17.78" length="middle"/>
<pin name="SPEEDLED" x="25.4" y="15.24" length="middle" rot="R180"/>
<pin name="ERX_JP" x="-27.94" y="20.32" length="middle"/>
<pin name="LINKLED" x="25.4" y="17.78" length="middle" rot="R180"/>
<pin name="ETX_JP" x="-27.94" y="22.86" length="middle"/>
<pin name="ERX_JM" x="25.4" y="20.32" length="middle" rot="R180"/>
<pin name="VCC3V@2" x="-27.94" y="25.4" length="middle"/>
<pin name="ETX_JM" x="25.4" y="22.86" length="middle" rot="R180"/>
<pin name="IRQ3" x="-27.94" y="27.94" length="middle"/>
<pin name="GND@2" x="25.4" y="25.4" length="middle" rot="R180"/>
<pin name="USBO_DM" x="-27.94" y="30.48" length="middle"/>
<pin name="IRQ2" x="25.4" y="27.94" length="middle" rot="R180"/>
<pin name="USBO_DP" x="25.4" y="30.48" length="middle" rot="R180"/>
<wire x1="-22.86" y1="-40.64" x2="-22.86" y2="33.02" width="0.254" layer="94"/>
<wire x1="-22.86" y1="33.02" x2="20.32" y2="33.02" width="0.254" layer="94"/>
<wire x1="20.32" y1="33.02" x2="20.32" y2="-40.64" width="0.254" layer="94"/>
<wire x1="20.32" y1="-40.64" x2="-22.86" y2="-40.64" width="0.254" layer="94"/>
<text x="-20.32" y="40.64" size="1.778" layer="95">&gt;NAME</text>
<text x="-20.32" y="35.56" size="1.778" layer="96">&gt;VALUE</text>
<pin name="T1IN" x="-27.94" y="-7.62" length="middle"/>
</symbol>
<symbol name="SMT-SVPF-OS-CON-CAP">
<wire x1="-2.54" y1="0" x2="0" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="0" x2="2.54" y2="0" width="0.254" layer="94"/>
<wire x1="0" y1="-1.016" x2="0" y2="-2.54" width="0.1524" layer="94"/>
<wire x1="0" y1="-1" x2="2.4892" y2="-1.8542" width="0.254" layer="94" curve="-37.878202"/>
<wire x1="-2.4668" y1="-1.8504" x2="0" y2="-1.0161" width="0.254" layer="94" curve="-37.373024"/>
<text x="1.016" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="1.016" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<pin name="A" x="0" y="5.08" visible="off" length="point" direction="pas" swaplevel="1" rot="R270"/>
<pin name="K" x="0" y="-5.08" visible="off" length="short" direction="pas" swaplevel="1" rot="R90"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.254" layer="94"/>
</symbol>
<symbol name="MLCC-X7R-CAP">
<wire x1="-7.62" y1="0" x2="-5.08" y2="0" width="0.254" layer="94"/>
<text x="-4.064" y="0.635" size="1.778" layer="95">&gt;NAME</text>
<text x="-4.064" y="-4.191" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-5.08" y="2.54" visible="off" length="point" direction="pas" swaplevel="1" rot="R270"/>
<pin name="2" x="-5.08" y="-5.08" visible="off" length="point" direction="pas" swaplevel="1" rot="R90"/>
<wire x1="-5.08" y1="0" x2="-2.54" y2="0" width="0.254" layer="94"/>
<wire x1="-7.62" y1="-1.27" x2="-5.08" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-1.27" x2="-2.54" y2="-1.27" width="0.254" layer="94"/>
<wire x1="-5.08" y1="-1.27" x2="-5.08" y2="-5.08" width="0.254" layer="94"/>
<wire x1="-5.08" y1="0" x2="-5.08" y2="2.54" width="0.254" layer="94"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="LTM4609MPV#PBF" prefix="U#" uservalue="yes">
<description>Per LTC Datasheet 4609fe LTM4609 (c) Samudra Haque, N3RDX, 2/23/2014</description>
<gates>
<gate name="G$1" symbol="LTM4609.SCH" x="0" y="2.54"/>
</gates>
<devices>
<device name="ROHS/HITEMP" package="LGA-141-LTC-05-08-1840-B">
<connects>
<connect gate="G$1" pin="COMP" pad="B7"/>
<connect gate="G$1" pin="EXTV_CC" pad="F6"/>
<connect gate="G$1" pin="FCB" pad="A9"/>
<connect gate="G$1" pin="INTV_CC" pad="F5"/>
<connect gate="G$1" pin="PGND" pad="A1 A2 A3 A11 A12 B1 B2 B3 B4 B10 B11 B12 C1 C2 C3 C4 C5 C6 C7 C8 C9 C10 C11 C12 D1 D2 D3 D4 D5 D6 D7 D8 D9 D10 D11 D12 E3 E4 E5 E6 E7 E8 E9 E10 E11 E12"/>
<connect gate="G$1" pin="PGOOD" pad="B5"/>
<connect gate="G$1" pin="PLLFLTR" pad="B8"/>
<connect gate="G$1" pin="PLLIN" pad="B9"/>
<connect gate="G$1" pin="RUN" pad="A8"/>
<connect gate="G$1" pin="R_SENSE" pad="F10 F11 F12 G5 G6 G7 G8 G9 G10 G11 G12 H5 H6 H7 H8 H9 H10 H11 H12 J5 J6 J7 K5 K6 L5 L6 M5 M6"/>
<connect gate="G$1" pin="SENSE+" pad="A4"/>
<connect gate="G$1" pin="SENSE-" pad="A5"/>
<connect gate="G$1" pin="SGND" pad="A7"/>
<connect gate="G$1" pin="SS" pad="A6"/>
<connect gate="G$1" pin="STBYMD" pad="A10"/>
<connect gate="G$1" pin="SW1" pad="SW1@J1 SW1@J2 SW1@J3 SW1@J4 SW1@K1 SW1@K2 SW1@K3 SW1@K4 SW1@L1 SW1@L2 SW1@L3 SW1@L4 SW1@M1 SW1@M2 SW1@M3 SW1@M4"/>
<connect gate="G$1" pin="SW2" pad="J8 J9 K7 K8 K9 L7 L8 L9 M7 M8 M9"/>
<connect gate="G$1" pin="V_FB" pad="B6"/>
<connect gate="G$1" pin="V_IN" pad="J10 J11 J12 K10 K11 K12 L10 L11 L12 M10 M11 M12"/>
<connect gate="G$1" pin="V_OUT" pad="E1 E2 F1 F2 F3 F4 G1 G2 G3 G4 H2 H3 H4 VOUT"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MSS1048" prefix="L">
<gates>
<gate name="G$1" symbol="SHIELDED-POWER-INDUCTOR" x="0" y="2.54"/>
</gates>
<devices>
<device name="-334KL_" package="MSS1048">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="MSS1038" prefix="L" uservalue="yes">
<gates>
<gate name="G$1" symbol="SHIELDED-POWER-INDUCTOR" x="0" y="0"/>
</gates>
<devices>
<device name="-333ML_" package="MSS1048">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="CSK-BUS-CONN" prefix="J" uservalue="yes">
<description>&lt;h1&gt;Cubesat Kit Bus Connector&lt;/h1&gt;
&lt;h2&gt;2 x Samtec ESQ-126-39-G-D Connectors&lt;/h2&gt;
&lt;p&gt;
104 pins per Cubesat Kit Bus Spec A5</description>
<gates>
<gate name="G$1" symbol="CUBESAT-KIT-BUS-A5" x="0" y="0"/>
</gates>
<devices>
<device name="2X2X26" package="CSK-BUS-PKG">
<connects>
<connect gate="G$1" pin="+5V_SW" pad="33"/>
<connect gate="G$1" pin="+5V_SYS@1" pad="77"/>
<connect gate="G$1" pin="+5V_SYS@2" pad="78"/>
<connect gate="G$1" pin="+5V_USB" pad="32"/>
<connect gate="G$1" pin="-CTS_MHX" pad="35"/>
<connect gate="G$1" pin="-DSR_MHX" pad="37"/>
<connect gate="G$1" pin="-DTR_MHX" pad="38"/>
<connect gate="G$1" pin="-FAULT" pad="25"/>
<connect gate="G$1" pin="-RESET" pad="29"/>
<connect gate="G$1" pin="-RST_MHX" pad="34"/>
<connect gate="G$1" pin="-RTS_MHX" pad="36"/>
<connect gate="G$1" pin="GND@1" pad="81"/>
<connect gate="G$1" pin="GND@2" pad="82"/>
<connect gate="G$1" pin="GND@3" pad="83"/>
<connect gate="G$1" pin="GND@4" pad="84"/>
<connect gate="G$1" pin="OFF_VCC" pad="31"/>
<connect gate="G$1" pin="P1.0" pad="68"/>
<connect gate="G$1" pin="P1.1" pad="67"/>
<connect gate="G$1" pin="P1.2" pad="66"/>
<connect gate="G$1" pin="P1.3" pad="65"/>
<connect gate="G$1" pin="P1.4" pad="64"/>
<connect gate="G$1" pin="P1.5" pad="63"/>
<connect gate="G$1" pin="P1.6" pad="62"/>
<connect gate="G$1" pin="P1.7" pad="61"/>
<connect gate="G$1" pin="P2.0" pad="76"/>
<connect gate="G$1" pin="P2.1" pad="75"/>
<connect gate="G$1" pin="P2.2" pad="74"/>
<connect gate="G$1" pin="P2.3" pad="73"/>
<connect gate="G$1" pin="P2.4" pad="72"/>
<connect gate="G$1" pin="P2.5" pad="71"/>
<connect gate="G$1" pin="P2.6" pad="70"/>
<connect gate="G$1" pin="P2.7" pad="69"/>
<connect gate="G$1" pin="P3.0" pad="24"/>
<connect gate="G$1" pin="P3.1" pad="23"/>
<connect gate="G$1" pin="P3.2" pad="22"/>
<connect gate="G$1" pin="P3.3" pad="21"/>
<connect gate="G$1" pin="P3.4" pad="20"/>
<connect gate="G$1" pin="P3.5" pad="19"/>
<connect gate="G$1" pin="P3.6" pad="18"/>
<connect gate="G$1" pin="P3.7" pad="17"/>
<connect gate="G$1" pin="P4.0" pad="16"/>
<connect gate="G$1" pin="P4.1" pad="15"/>
<connect gate="G$1" pin="P4.2" pad="14"/>
<connect gate="G$1" pin="P4.3" pad="13"/>
<connect gate="G$1" pin="P4.4" pad="12"/>
<connect gate="G$1" pin="P4.5" pad="11"/>
<connect gate="G$1" pin="P4.6" pad="10"/>
<connect gate="G$1" pin="P4.7" pad="9"/>
<connect gate="G$1" pin="P5.0" pad="8"/>
<connect gate="G$1" pin="P5.1" pad="7"/>
<connect gate="G$1" pin="P5.2" pad="6"/>
<connect gate="G$1" pin="P5.3" pad="5"/>
<connect gate="G$1" pin="P5.4" pad="4"/>
<connect gate="G$1" pin="P5.5" pad="3"/>
<connect gate="G$1" pin="P5.6" pad="2"/>
<connect gate="G$1" pin="P5.7" pad="1"/>
<connect gate="G$1" pin="P6.0" pad="60"/>
<connect gate="G$1" pin="P6.1" pad="59"/>
<connect gate="G$1" pin="P6.2" pad="58"/>
<connect gate="G$1" pin="P6.3" pad="57"/>
<connect gate="G$1" pin="P6.4" pad="56"/>
<connect gate="G$1" pin="P6.5" pad="55"/>
<connect gate="G$1" pin="P6.6" pad="54"/>
<connect gate="G$1" pin="P6.7" pad="53"/>
<connect gate="G$1" pin="RSVD0" pad="44"/>
<connect gate="G$1" pin="RSVD1" pad="45"/>
<connect gate="G$1" pin="RSVD2" pad="46"/>
<connect gate="G$1" pin="RXD_MHX" pad="40"/>
<connect gate="G$1" pin="SCL_SYS" pad="43"/>
<connect gate="G$1" pin="SDA_SYS" pad="41"/>
<connect gate="G$1" pin="SENSE" pad="27"/>
<connect gate="G$1" pin="SW0@1" pad="85"/>
<connect gate="G$1" pin="SW0@2" pad="86"/>
<connect gate="G$1" pin="SW1@1" pad="87"/>
<connect gate="G$1" pin="SW1@2" pad="88"/>
<connect gate="G$1" pin="SW2@1" pad="89"/>
<connect gate="G$1" pin="SW2@2" pad="90"/>
<connect gate="G$1" pin="SW3@1" pad="91"/>
<connect gate="G$1" pin="SW3@2" pad="92"/>
<connect gate="G$1" pin="SW4@1" pad="93"/>
<connect gate="G$1" pin="SW4@2" pad="94"/>
<connect gate="G$1" pin="SW5@1" pad="95"/>
<connect gate="G$1" pin="SW5@2" pad="96"/>
<connect gate="G$1" pin="TXD_MHX" pad="39"/>
<connect gate="G$1" pin="USER0" pad="47"/>
<connect gate="G$1" pin="USER1" pad="48"/>
<connect gate="G$1" pin="USER10" pad="103"/>
<connect gate="G$1" pin="USER11" pad="104"/>
<connect gate="G$1" pin="USER2" pad="49"/>
<connect gate="G$1" pin="USER3" pad="50"/>
<connect gate="G$1" pin="USER4" pad="51"/>
<connect gate="G$1" pin="USER5" pad="52"/>
<connect gate="G$1" pin="USER6" pad="99"/>
<connect gate="G$1" pin="USER7" pad="100"/>
<connect gate="G$1" pin="USER8" pad="101"/>
<connect gate="G$1" pin="USER9" pad="102"/>
<connect gate="G$1" pin="VBACKUP" pad="42"/>
<connect gate="G$1" pin="VBATT@1" pad="97"/>
<connect gate="G$1" pin="VBATT@2" pad="98"/>
<connect gate="G$1" pin="VCC_SYS@1" pad="79"/>
<connect gate="G$1" pin="VCC_SYS@2" pad="80"/>
<connect gate="G$1" pin="VEREF+" pad="28"/>
<connect gate="G$1" pin="VREF+" pad="26"/>
<connect gate="G$1" pin="VREF-" pad="30"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="UCAT-4CU-B-CONTROL-UNIT">
<gates>
<gate name="G$1" symbol="UCAT-4CU-B-CONTROL-UNIT-DAUGHTERBOARD" x="7.62" y="-20.32"/>
</gates>
<devices>
<device name="NANO55415" package="MOLEX-MINI-PCI-EXPRESS-8MM-52CKT">
<connects>
<connect gate="G$1" pin="ADC_IN0" pad="2"/>
<connect gate="G$1" pin="ADC_IN1" pad="1"/>
<connect gate="G$1" pin="ADC_IN2" pad="4"/>
<connect gate="G$1" pin="ADC_IN3" pad="3"/>
<connect gate="G$1" pin="ADC_IN4" pad="6"/>
<connect gate="G$1" pin="ADC_IN7" pad="5"/>
<connect gate="G$1" pin="AGND" pad="8"/>
<connect gate="G$1" pin="CAN1_RX" pad="20"/>
<connect gate="G$1" pin="CAN1_TX" pad="22"/>
<connect gate="G$1" pin="ERX_JM" pad="44"/>
<connect gate="G$1" pin="ERX_JP" pad="43"/>
<connect gate="G$1" pin="ETX_JM" pad="46"/>
<connect gate="G$1" pin="ETX_JP" pad="45"/>
<connect gate="G$1" pin="GND@1" pad="18"/>
<connect gate="G$1" pin="GND@2" pad="48"/>
<connect gate="G$1" pin="I2C0_SCL" pad="27"/>
<connect gate="G$1" pin="I2C0_SDA" pad="29"/>
<connect gate="G$1" pin="IRQ2" pad="50"/>
<connect gate="G$1" pin="IRQ3" pad="49"/>
<connect gate="G$1" pin="IRQ7" pad="9"/>
<connect gate="G$1" pin="LINKLED" pad="42"/>
<connect gate="G$1" pin="OW_DAT" pad="12"/>
<connect gate="G$1" pin="RSTI" pad="11"/>
<connect gate="G$1" pin="SDHC_CLK" pad="31"/>
<connect gate="G$1" pin="SDHC_CMD" pad="33"/>
<connect gate="G$1" pin="SDHC_DAT0" pad="35"/>
<connect gate="G$1" pin="SDHC_DAT1" pad="37"/>
<connect gate="G$1" pin="SDHC_DAT2" pad="39"/>
<connect gate="G$1" pin="SDHC_DAT3" pad="15"/>
<connect gate="G$1" pin="SPEEDLED" pad="40"/>
<connect gate="G$1" pin="T0IN" pad="19"/>
<connect gate="G$1" pin="T1IN" pad="21"/>
<connect gate="G$1" pin="T2IN" pad="23"/>
<connect gate="G$1" pin="T3IN" pad="25"/>
<connect gate="G$1" pin="UART0_CTS" pad="30"/>
<connect gate="G$1" pin="UART0_RTS" pad="28"/>
<connect gate="G$1" pin="UART0_RX" pad="24"/>
<connect gate="G$1" pin="UART0_TX" pad="26"/>
<connect gate="G$1" pin="UART1_CTS" pad="38"/>
<connect gate="G$1" pin="UART1_RTS" pad="36"/>
<connect gate="G$1" pin="UART1_RX" pad="32"/>
<connect gate="G$1" pin="UART1_TX" pad="34"/>
<connect gate="G$1" pin="UART2_CTS" pad="10"/>
<connect gate="G$1" pin="UART2_RTS" pad="14"/>
<connect gate="G$1" pin="UART2_RX" pad="13"/>
<connect gate="G$1" pin="UART2_TX" pad="16"/>
<connect gate="G$1" pin="USBO_DM" pad="51"/>
<connect gate="G$1" pin="USBO_DP" pad="52"/>
<connect gate="G$1" pin="VCC3V@1" pad="17"/>
<connect gate="G$1" pin="VCC3V@2" pad="47"/>
<connect gate="G$1" pin="VCC3VE" pad="41"/>
<connect gate="G$1" pin="VDDA_DAC_ADC" pad="7"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="OSCON-50SVPF" prefix="C" uservalue="yes">
<gates>
<gate name="G$1" symbol="SMT-SVPF-OS-CON-CAP" x="-5.08" y="0"/>
</gates>
<devices>
<device name="68M" package="OS-CON-SVPF-F12">
<connects>
<connect gate="G$1" pin="A" pad="A1"/>
<connect gate="G$1" pin="K" pad="K1"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
<deviceset name="AVX-LD105C475KAB2A" prefix="C" uservalue="yes">
<gates>
<gate name="G$1" symbol="MLCC-X7R-CAP" x="0" y="0"/>
</gates>
<devices>
<device name="" package="MLCC-X7R-1210">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="frames">
<description>&lt;b&gt;Frames for Sheet and Layout&lt;/b&gt;</description>
<packages>
</packages>
<symbols>
<symbol name="FRAME_A_L">
<frame x1="0" y1="0" x2="279.4" y2="215.9" columns="6" rows="5" layer="94" border-bottom="no"/>
</symbol>
<symbol name="DOCFIELD">
<wire x1="0" y1="0" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="87.63" y2="15.24" width="0.1016" layer="94"/>
<wire x1="0" y1="0" x2="0" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="71.12" y2="5.08" width="0.1016" layer="94"/>
<wire x1="0" y1="5.08" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="101.6" y1="15.24" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="71.12" y2="0" width="0.1016" layer="94"/>
<wire x1="71.12" y1="5.08" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="71.12" y1="0" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="87.63" y2="5.08" width="0.1016" layer="94"/>
<wire x1="87.63" y1="15.24" x2="0" y2="15.24" width="0.1016" layer="94"/>
<wire x1="87.63" y1="5.08" x2="101.6" y2="5.08" width="0.1016" layer="94"/>
<wire x1="101.6" y1="5.08" x2="101.6" y2="0" width="0.1016" layer="94"/>
<wire x1="0" y1="15.24" x2="0" y2="22.86" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="35.56" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="101.6" y2="22.86" width="0.1016" layer="94"/>
<wire x1="0" y1="22.86" x2="0" y2="35.56" width="0.1016" layer="94"/>
<wire x1="101.6" y1="22.86" x2="101.6" y2="15.24" width="0.1016" layer="94"/>
<text x="1.27" y="1.27" size="2.54" layer="94" font="vector">Date:</text>
<text x="12.7" y="1.27" size="2.54" layer="94" font="vector">&gt;LAST_DATE_TIME</text>
<text x="72.39" y="1.27" size="2.54" layer="94" font="vector">Sheet:</text>
<text x="86.36" y="1.27" size="2.54" layer="94" font="vector">&gt;SHEET</text>
<text x="88.9" y="11.43" size="2.54" layer="94" font="vector">REV:</text>
<text x="1.27" y="19.05" size="2.54" layer="94" font="vector">TITLE:</text>
<text x="1.27" y="11.43" size="2.54" layer="94" font="vector">Document Number:</text>
<text x="17.78" y="19.05" size="2.54" layer="94" font="vector">&gt;DRAWING_NAME</text>
</symbol>
</symbols>
<devicesets>
<deviceset name="FRAME_A_L" prefix="FRAME" uservalue="yes">
<description>&lt;b&gt;FRAME&lt;/b&gt; A Size , 8 1/2 x 11 INCH, Landscape&lt;p&gt;</description>
<gates>
<gate name="G$1" symbol="FRAME_A_L" x="0" y="0" addlevel="always"/>
<gate name="G$2" symbol="DOCFIELD" x="172.72" y="0" addlevel="always"/>
</gates>
<devices>
<device name="">
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="pinhead">
<description>&lt;b&gt;Pin Header Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="1X02">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-1.905" y1="1.27" x2="-0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="1.27" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="-0.635" x2="-0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="-1.905" y1="1.27" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="-0.635" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="-0.635" y1="-1.27" x2="-1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="0.635" y2="1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="1.27" x2="1.905" y2="1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="1.27" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="2.54" y2="-0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-0.635" x2="1.905" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="1.905" y1="-1.27" x2="0.635" y2="-1.27" width="0.1524" layer="21"/>
<wire x1="0.635" y1="-1.27" x2="0" y2="-0.635" width="0.1524" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1.016" shape="long" rot="R90"/>
<text x="-2.6162" y="1.8288" size="1.27" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-3.175" size="1.27" layer="27">&gt;VALUE</text>
<rectangle x1="-1.524" y1="-0.254" x2="-1.016" y2="0.254" layer="51"/>
<rectangle x1="1.016" y1="-0.254" x2="1.524" y2="0.254" layer="51"/>
</package>
<package name="1X02/90">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<wire x1="-2.54" y1="-1.905" x2="0" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="0" y1="-1.905" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="0" y1="0.635" x2="-2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="-2.54" y1="0.635" x2="-2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="-1.27" y1="6.985" x2="-1.27" y2="1.27" width="0.762" layer="21"/>
<wire x1="0" y1="-1.905" x2="2.54" y2="-1.905" width="0.1524" layer="21"/>
<wire x1="2.54" y1="-1.905" x2="2.54" y2="0.635" width="0.1524" layer="21"/>
<wire x1="2.54" y1="0.635" x2="0" y2="0.635" width="0.1524" layer="21"/>
<wire x1="1.27" y1="6.985" x2="1.27" y2="1.27" width="0.762" layer="21"/>
<pad name="1" x="-1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="-3.81" drill="1.016" shape="long" rot="R90"/>
<text x="-3.175" y="-3.81" size="1.27" layer="25" ratio="10" rot="R90">&gt;NAME</text>
<text x="4.445" y="-3.81" size="1.27" layer="27" rot="R90">&gt;VALUE</text>
<rectangle x1="-1.651" y1="0.635" x2="-0.889" y2="1.143" layer="21"/>
<rectangle x1="0.889" y1="0.635" x2="1.651" y2="1.143" layer="21"/>
<rectangle x1="-1.651" y1="-2.921" x2="-0.889" y2="-1.905" layer="21"/>
<rectangle x1="0.889" y1="-2.921" x2="1.651" y2="-1.905" layer="21"/>
</package>
</packages>
<symbols>
<symbol name="PINHD2">
<wire x1="-6.35" y1="-2.54" x2="1.27" y2="-2.54" width="0.4064" layer="94"/>
<wire x1="1.27" y1="-2.54" x2="1.27" y2="5.08" width="0.4064" layer="94"/>
<wire x1="1.27" y1="5.08" x2="-6.35" y2="5.08" width="0.4064" layer="94"/>
<wire x1="-6.35" y1="5.08" x2="-6.35" y2="-2.54" width="0.4064" layer="94"/>
<text x="-6.35" y="5.715" size="1.778" layer="95">&gt;NAME</text>
<text x="-6.35" y="-5.08" size="1.778" layer="96">&gt;VALUE</text>
<pin name="1" x="-2.54" y="2.54" visible="pad" length="short" direction="pas" function="dot"/>
<pin name="2" x="-2.54" y="0" visible="pad" length="short" direction="pas" function="dot"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="PINHD-1X2" prefix="JP" uservalue="yes">
<description>&lt;b&gt;PIN HEADER&lt;/b&gt;</description>
<gates>
<gate name="G$1" symbol="PINHD2" x="0" y="0"/>
</gates>
<devices>
<device name="" package="1X02">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
<device name="/90" package="1X02/90">
<connects>
<connect gate="G$1" pin="1" pad="1"/>
<connect gate="G$1" pin="2" pad="2"/>
</connects>
<technologies>
<technology name=""/>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
<library name="con-molex">
<description>&lt;b&gt;Molex Connectors&lt;/b&gt;&lt;p&gt;
&lt;author&gt;Created by librarian@cadsoft.de&lt;/author&gt;</description>
<packages>
<package name="22-23-2021">
<description>.100" (2.54mm) Center Headers - 2 Pin</description>
<wire x1="-2.54" y1="3.175" x2="2.54" y2="3.175" width="0.254" layer="21"/>
<wire x1="2.54" y1="3.175" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="2.54" y1="1.27" x2="2.54" y2="-3.175" width="0.254" layer="21"/>
<wire x1="2.54" y1="-3.175" x2="-2.54" y2="-3.175" width="0.254" layer="21"/>
<wire x1="-2.54" y1="-3.175" x2="-2.54" y2="1.27" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="-2.54" y2="3.175" width="0.254" layer="21"/>
<wire x1="-2.54" y1="1.27" x2="2.54" y2="1.27" width="0.254" layer="21"/>
<pad name="1" x="-1.27" y="0" drill="1" shape="long" rot="R90"/>
<pad name="2" x="1.27" y="0" drill="1" shape="long" rot="R90"/>
<text x="-2.54" y="3.81" size="1.016" layer="25" ratio="10">&gt;NAME</text>
<text x="-2.54" y="-5.08" size="1.016" layer="27" ratio="10">&gt;VALUE</text>
</package>
</packages>
<symbols>
<symbol name="MV">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<text x="-0.762" y="1.397" size="1.778" layer="96">&gt;VALUE</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
<symbol name="M">
<wire x1="1.27" y1="0" x2="0" y2="0" width="0.6096" layer="94"/>
<text x="2.54" y="-0.762" size="1.524" layer="95">&gt;NAME</text>
<pin name="S" x="-2.54" y="0" visible="off" length="short" direction="pas"/>
</symbol>
</symbols>
<devicesets>
<deviceset name="22-23-2021" prefix="X">
<description>.100" (2.54mm) Center Header - 2 Pin</description>
<gates>
<gate name="-1" symbol="MV" x="0" y="0" addlevel="always" swaplevel="1"/>
<gate name="-2" symbol="M" x="0" y="-2.54" addlevel="always" swaplevel="1"/>
</gates>
<devices>
<device name="" package="22-23-2021">
<connects>
<connect gate="-1" pin="S" pad="1"/>
<connect gate="-2" pin="S" pad="2"/>
</connects>
<technologies>
<technology name="">
<attribute name="MF" value="MOLEX" constant="no"/>
<attribute name="MPN" value="22-23-2021" constant="no"/>
<attribute name="OC_FARNELL" value="1462926" constant="no"/>
<attribute name="OC_NEWARK" value="25C3832" constant="no"/>
</technology>
</technologies>
</device>
</devices>
</deviceset>
</devicesets>
</library>
</libraries>
<attributes>
</attributes>
<variantdefs>
</variantdefs>
<classes>
<class number="0" name="default" width="0" drill="0">
<clearance class="0" value="0.205"/>
</class>
</classes>
<parts>
<part name="H1" library="mpnl_holes" deviceset="MOUNT-PAD-ROUND" device="CSK_MTG_HOLE_A5"/>
<part name="HBL" library="mpnl_holes" deviceset="MOUNT-PAD-ROUND" device="CSK_MTG_HOLE_A5"/>
<part name="H2" library="mpnl_holes" deviceset="MOUNT-PAD-ROUND" device="CSK_MTG_HOLE_A5"/>
<part name="H3" library="mpnl_holes" deviceset="MOUNT-PAD-ROUND" device="CSK_MTG_HOLE_A5"/>
<part name="U2" library="gwu_mpnl_ucat_v8" deviceset="LTM4609MPV#PBF" device="ROHS/HITEMP" value="LTM4609MPV#PBF"/>
<part name="SUPPLY5" library="supply2" deviceset="GND" device=""/>
<part name="L1" library="gwu_mpnl_ucat_v8" deviceset="MSS1048" device="-334KL_"/>
<part name="L2" library="gwu_mpnl_ucat_v8" deviceset="MSS1038" device="-333ML_"/>
<part name="J2" library="gwu_mpnl_ucat_v8" deviceset="CSK-BUS-CONN" device="2X2X26"/>
<part name="FRAME1" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="FRAME2" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="JP1" library="pinhead" deviceset="PINHD-1X2" device=""/>
<part name="X1" library="con-molex" deviceset="22-23-2021" device=""/>
<part name="FRAME3" library="frames" deviceset="FRAME_A_L" device=""/>
<part name="U1" library="gwu_mpnl_ucat_v8" deviceset="UCAT-4CU-B-CONTROL-UNIT" device="NANO55415"/>
<part name="C1" library="gwu_mpnl_ucat_v8" deviceset="OSCON-50SVPF" device="68M" value="68uF"/>
<part name="C2" library="gwu_mpnl_ucat_v8" deviceset="AVX-LD105C475KAB2A" device="" value="4.7uF"/>
<part name="SUPPLY2" library="supply2" deviceset="GND" device=""/>
<part name="SUPPLY1" library="supply2" deviceset="GND" device=""/>
</parts>
<sheets>
<sheet>
<plain>
<text x="27.94" y="-71.12" size="3.81" layer="97">Spacecraft Bus Interface Section</text>
</plain>
<instances>
<instance part="J2" gate="G$1" x="-35.56" y="15.24"/>
<instance part="FRAME1" gate="G$1" x="-157.48" y="-99.06"/>
<instance part="FRAME1" gate="G$2" x="15.24" y="-99.06"/>
<instance part="JP1" gate="G$1" x="-71.12" y="35.56" rot="R180"/>
<instance part="X1" gate="-1" x="48.26" y="78.74" rot="R90"/>
<instance part="X1" gate="-2" x="50.8" y="78.74" rot="R90"/>
</instances>
<busses>
</busses>
<nets>
<net name="I2C(CLK)" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="SCL_SYS"/>
<wire x1="-58.42" y1="33.02" x2="-68.58" y2="33.02" width="0.1524" layer="91"/>
<wire x1="-76.2" y1="33.02" x2="-76.2" y2="27.94" width="0.1524" layer="91"/>
<wire x1="-76.2" y1="27.94" x2="-81.28" y2="27.94" width="0.1524" layer="91"/>
<label x="-81.28" y="27.94" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="1"/>
<wire x1="-76.2" y1="33.02" x2="-68.58" y2="33.02" width="0.1524" layer="91"/>
</segment>
</net>
<net name="I2C(DATA)" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="SDA_SYS"/>
<wire x1="-58.42" y1="35.56" x2="-68.58" y2="35.56" width="0.1524" layer="91"/>
<wire x1="-76.2" y1="35.56" x2="-76.2" y2="40.64" width="0.1524" layer="91"/>
<wire x1="-76.2" y1="40.64" x2="-81.28" y2="40.64" width="0.1524" layer="91"/>
<label x="-81.28" y="40.64" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="JP1" gate="G$1" pin="2"/>
<wire x1="-76.2" y1="35.56" x2="-68.58" y2="35.56" width="0.1524" layer="91"/>
</segment>
</net>
<net name="VIN" class="0">
<segment>
<pinref part="J2" gate="G$1" pin="VBATT@1"/>
<wire x1="-58.42" y1="-48.26" x2="-76.2" y2="-48.26" width="0.1524" layer="91"/>
<label x="-76.2" y="-48.26" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
<segment>
<pinref part="J2" gate="G$1" pin="VBATT@2"/>
<wire x1="-12.7" y1="-48.26" x2="2.54" y2="-48.26" width="0.1524" layer="91"/>
<label x="2.54" y="-48.26" size="1.27" layer="95" xref="yes"/>
</segment>
</net>
<net name="PGND" class="0">
<segment>
<pinref part="X1" gate="-2" pin="S"/>
<wire x1="50.8" y1="76.2" x2="50.8" y2="63.5" width="0.1524" layer="91"/>
<wire x1="50.8" y1="63.5" x2="43.18" y2="63.5" width="0.1524" layer="91"/>
<label x="43.18" y="63.5" size="1.27" layer="95" rot="MR0" xref="yes"/>
</segment>
</net>
<net name="SW3V+" class="0">
<segment>
<pinref part="X1" gate="-1" pin="S"/>
<wire x1="48.26" y1="76.2" x2="48.26" y2="68.58" width="0.1524" layer="91"/>
<wire x1="48.26" y1="68.58" x2="43.18" y2="68.58" width="0.1524" layer="91"/>
<label x="43.18" y="68.58" size="1.27" layer="95" rot="MR0" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<plain>
<text x="33.02" y="-104.14" size="3.81" layer="97">Power Management Section</text>
</plain>
<instances>
<instance part="H1" gate="G$1" x="-119.38" y="71.12"/>
<instance part="HBL" gate="G$1" x="-119.38" y="60.96"/>
<instance part="H2" gate="G$1" x="-119.38" y="50.8"/>
<instance part="H3" gate="G$1" x="-119.38" y="40.64"/>
<instance part="U2" gate="G$1" x="10.16" y="-25.4"/>
<instance part="SUPPLY5" gate="GND" x="38.1" y="-55.88"/>
<instance part="L1" gate="G$1" x="66.04" y="15.24"/>
<instance part="L2" gate="G$1" x="10.16" y="40.64"/>
<instance part="FRAME2" gate="G$1" x="-144.78" y="-132.08"/>
<instance part="FRAME2" gate="G$2" x="27.94" y="-132.08"/>
<instance part="C1" gate="G$1" x="-12.7" y="17.78"/>
<instance part="C2" gate="G$1" x="27.94" y="17.78"/>
<instance part="SUPPLY2" gate="GND" x="22.86" y="10.16"/>
<instance part="SUPPLY1" gate="GND" x="-12.7" y="10.16"/>
</instances>
<busses>
</busses>
<nets>
<net name="PGND" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="PGND"/>
<pinref part="SUPPLY5" gate="GND" pin="GND"/>
<wire x1="38.1" y1="-50.8" x2="38.1" y2="-53.34" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SW2" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="SW2"/>
<pinref part="L1" gate="G$1" pin="1"/>
<wire x1="38.1" y1="-5.08" x2="58.42" y2="-5.08" width="0.1524" layer="91"/>
<wire x1="58.42" y1="-5.08" x2="60.96" y2="-2.54" width="0.1524" layer="91"/>
<wire x1="60.96" y1="-2.54" x2="60.96" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="SW1" class="0">
<segment>
<pinref part="U2" gate="G$1" pin="SW1"/>
<pinref part="L1" gate="G$1" pin="2"/>
<wire x1="38.1" y1="-15.24" x2="68.58" y2="-15.24" width="0.1524" layer="91"/>
<wire x1="68.58" y1="-15.24" x2="71.12" y2="-12.7" width="0.1524" layer="91"/>
<wire x1="71.12" y1="-12.7" x2="71.12" y2="0" width="0.1524" layer="91"/>
</segment>
</net>
<net name="V_IN" class="0">
<segment>
<pinref part="L2" gate="G$1" pin="2"/>
<wire x1="15.24" y1="25.4" x2="17.78" y2="22.86" width="0.1524" layer="91"/>
<wire x1="17.78" y1="22.86" x2="22.86" y2="22.86" width="0.1524" layer="91"/>
<wire x1="22.86" y1="22.86" x2="35.56" y2="22.86" width="0.1524" layer="91"/>
<wire x1="35.56" y1="22.86" x2="40.64" y2="17.78" width="0.1524" layer="91"/>
<wire x1="40.64" y1="17.78" x2="40.64" y2="2.54" width="0.1524" layer="91"/>
<pinref part="U2" gate="G$1" pin="V_IN"/>
<wire x1="40.64" y1="2.54" x2="38.1" y2="0" width="0.1524" layer="91"/>
<pinref part="C2" gate="G$1" pin="1"/>
<wire x1="22.86" y1="20.32" x2="22.86" y2="22.86" width="0.1524" layer="91"/>
<junction x="22.86" y="22.86"/>
</segment>
</net>
<net name="VIN" class="0">
<segment>
<wire x1="-12.7" y1="22.86" x2="-22.86" y2="22.86" width="0.1524" layer="91"/>
<label x="-22.86" y="22.86" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="C1" gate="G$1" pin="A"/>
<junction x="-12.7" y="22.86"/>
<pinref part="L2" gate="G$1" pin="1"/>
<wire x1="-12.7" y1="22.86" x2="2.54" y2="22.86" width="0.1524" layer="91"/>
<wire x1="2.54" y1="22.86" x2="5.08" y2="25.4" width="0.1524" layer="91"/>
</segment>
</net>
<net name="GND" class="0">
<segment>
<pinref part="C2" gate="G$1" pin="2"/>
<pinref part="SUPPLY2" gate="GND" pin="GND"/>
</segment>
<segment>
<pinref part="C1" gate="G$1" pin="K"/>
<pinref part="SUPPLY1" gate="GND" pin="GND"/>
</segment>
</net>
</nets>
</sheet>
<sheet>
<plain>
<text x="88.9" y="-43.18" size="3.81" layer="97">Control Unit</text>
</plain>
<instances>
<instance part="FRAME3" gate="G$1" x="-88.9" y="-71.12"/>
<instance part="FRAME3" gate="G$2" x="83.82" y="-71.12"/>
<instance part="U1" gate="G$1" x="50.8" y="38.1"/>
</instances>
<busses>
</busses>
<nets>
<net name="SW3V+" class="0">
<segment>
<wire x1="22.86" y1="25.4" x2="2.54" y2="25.4" width="0.1524" layer="91"/>
<label x="2.54" y="25.4" size="1.27" layer="95" rot="R180" xref="yes"/>
<pinref part="U1" gate="G$1" pin="VCC3V@1"/>
</segment>
<segment>
<pinref part="U1" gate="G$1" pin="VCC3V@2"/>
<wire x1="22.86" y1="63.5" x2="2.54" y2="63.5" width="0.1524" layer="91"/>
<label x="2.54" y="63.5" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="I2C(DATA)" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="I2C0_SDA"/>
<wire x1="22.86" y1="40.64" x2="7.62" y2="40.64" width="0.1524" layer="91"/>
<wire x1="7.62" y1="40.64" x2="7.62" y2="43.18" width="0.1524" layer="91"/>
<wire x1="7.62" y1="43.18" x2="2.54" y2="43.18" width="0.1524" layer="91"/>
<label x="2.54" y="43.18" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
<net name="I2C(CLK)" class="0">
<segment>
<pinref part="U1" gate="G$1" pin="I2C0_SCL"/>
<wire x1="22.86" y1="38.1" x2="7.62" y2="38.1" width="0.1524" layer="91"/>
<wire x1="7.62" y1="38.1" x2="7.62" y2="35.56" width="0.1524" layer="91"/>
<wire x1="7.62" y1="35.56" x2="2.54" y2="35.56" width="0.1524" layer="91"/>
<label x="2.54" y="35.56" size="1.27" layer="95" rot="R180" xref="yes"/>
</segment>
</net>
</nets>
</sheet>
</sheets>
<errors>
<approved hash="108,2,71.12,20.32,N$5,,,,,"/>
<approved hash="108,2,68.58,55.88,N$5,,,,,"/>
<approved hash="108,2,86.36,88.9,N$6,,,,,"/>
</errors>
</schematic>
</drawing>
<compatibility>
<note version="6.3" minversion="6.2.2" severity="warning">
Since Version 6.2.2 text objects can contain more than one line,
which will not be processed correctly with this version.
</note>
</compatibility>
</eagle>
