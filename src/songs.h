#ifndef CHOSEN_SONG
#define CHOSEN_SONG 6
// 2 Vader Jacob
// 3 Papegaaitje leef je nog
// 4 Slaap kindje slaap
// 5 Jingle Bells
// 6 Never gonna give you up
//

#if CHOSEN_SONG == 0
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 120]"
"c1/1"
"d e"
"_1/1"
"f g a"
"_1/1"
"a g f e g e d";

#elif CHOSEN_SONG == 1
const char songNotes[] PROGMEM =
"c3/8 d"
"c d";

#elif CHOSEN_SONG == 2    // Vader Jacob
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 120]"
"cdec cdec"
"ef g1/2"
"ef g1/2"
"g1/8 a1/8 g1/8 f1/8 e c"
"g1/8 a1/8 g1/8 f1/8 e c"
"c [oct=3]g[oct=4] c1/2"
"c [oct=3]g[oct=4] c1/2";

#elif CHOSEN_SONG == 3    // Papegaaitje leef je nog?
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 114]"
"d d1/8 d F1/8 a F1/8 d3/8"
"e3/8 e3/8 C3/8 [oct=3]a3/8[oct=4]"
"d d1/8 d F1/8 a F1/8 d3/8"
"e3/8 e3/8 C3/8 [oct=3]a3/8[oct=4]"
"d d1/8 d d1/8 d d1/8 d d1/8 d d1/8 d d1/8 d d1/8 d3/8"
"d3/8 F3/8 a3/8 F3/8 [oct=5]d3/8 _3/8";

#elif CHOSEN_SONG == 4    // Slaap kindje slaap
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 95]"
"";

#elif CHOSEN_SONG == 5    // Jingle bells
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 104]"
"eee1/2 eee1/2"
"egc d1/8 e1/1"
"fff f1/8f eee e1/8e1/8"
"edde d1/2g1/2 eee1/2 eee1/2"
"egc d1/8 e1/1 ffff"
"fee e1/8e1/8 ggfd c1/1";

#elif CHOSEN_SONG == 6    // Never gonna give you up //https://virtualpiano.net/?song-post-10680
const char songNotes[] PROGMEM =
"[octave = 4; bpm = 113]"

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _"
//1 /C4D4F4D4A4 A4 G4| 

"c1/8 d1/8 f1/8 d1/8 g g f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8"
//1.3 /C4D4F4D4G4 G4 F4 E4D4 C4D4F4D4F4|
"[img = /music/NeverGonnaGiveYouUp/0.bmp]"

"g e d1/8 c c c g1/8 _1/8 f1/8 _3/8"
//1.6 /G4 E4 D4C4 C4 C4 G4|F4||

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _"
//2 /C4D4F4D4A4 A4 G4| 
"[img = /music/NeverGonnaGiveYouUp/1.bmp]"

"c1/8 d1/8 f1/8 d1/8 [oct=5]c1/8[oct=4] _1/8"
//2.25 /C4D4F4D4C5|

"e f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8"
//2.5 /E4 F4 E4D4 C4D4F4D4F4|

"g e d1/8 c1/8 _1/8 c1/8 g1/8 _1/8 f1/8 _3/8"
//2.75 /G4 E4 D4C4|C4 G4|F4||
"[img = /music/NeverGonnaGiveYouUp/2.bmp]"

"d f d f g1/8 _3/8 e d c1/8 _3/8"
//3 /D4 F4 D4 F4 G4||E4 D4 C4||

"d d e f d c1/8 _ [oct=5]c c[oct=4] g1/8 _1/8 a g f1/8 _1/8"
//4 /D4 D4 E4 F4 D4 C4| C5 C5 G4|A4 G4 F4|

"d f d f d f g1/8 _1/8 e d c1/8 _3/8 d d e f d c _3/8"
//5 /D4 F4 D4 F4 D4 F4 G4|E4 D4 C4||D4 D4 E4 F4 D4 C4||

"g g a1/8 _1/8 g1/8 _ f1/8 _3/8"
//6 /G4 G4 A4|G4| F4||

"g a g1/8 _1/8 g g a g c c1/8 _3/8 c d e f d1/8 _1/8 g a g1/8 _1/8"
//7 /G4 A4 G4|G4 G4 A4 G4 C4 C4||C4 D4 E4 F4 D4|G4 A4 G4|

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _ c1/8 d1/8 f1/8 d1/8 g1/8 g f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8 g e d1/8 c1/8 _1/8"
"c g1/8 _1/8 f1/8 _3/8"
//8 /C4D4F4D4A4 A4 G4| C4D4F4D4G4 G4 F4 E4D4 C4D4F4D4F4|G4 E4 D4C4|
//  /C4 G4|F4||

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _ c1/8 d1/8 f1/8 d1/8 [oct=5]c1/8[oct=4]_1/8 e f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8 g e d1/8 c1/8 _1/8"
"c g1/8 _1/8 f1/8 _3/8"
//9 /C4D4F4D4A4 A4 G4| C4D4F4D4C5|E4 F4 E4D4 C4D4F4D4F4|G4 E4 D4C4|
//  /C4 G4|F4||

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _ c1/8 d1/8 f1/8 d1/8 g g f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8"
"g e d1/8 c c c g1/8 _1/8 f _"
//10 /C4D4F4D4A4 A4 G4| C4D4F4D4G4 G4 F4 E4D4 C4D4F4D4F4|
//   /G4 E4 D4C4 C4 C4 G4|F4||

"c1/8 d1/8 f1/8 d1/8 a a g1/8 _ c1/8 d1/8 f1/8 d1/8 g g f e1/8 d c1/8 d1/8 f1/8 d1/8 f1/8 _1/8 g e d1/8 c1/8 _1/8"
"c g1/8 _1/8 f";
//11 /C4D4F4D4A4 A4 G4| C4D4F4D4G4 G4 F4 E4D4 C4D4F4D4F4|G4 E4 D4C4|
//   /C4 G4|F4

#endif // if else block
#endif // if n def