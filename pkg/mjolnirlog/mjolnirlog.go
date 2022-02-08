/**
 * @author      : dog head
 * @date        : Created in 2022/1/21
 * @mail        : 396139919@qq.com
 * @project     : Mjolnir
 * @file        : mjolnirlog.go
 * @description : TODO
 */

package mjolnirlog

import "fmt"

const (
	LevelInfo    = "Info"
	LevelTrace   = "Trace"
	LevelDebug   = "Debug"
	LevelWarning = "Warning"
	LevelError   = "Error"
	LevelPanic   = "Panic"
)

type logger struct {
}

func PrintLogo() {
	str := `
++++++++++++++++++++++++++++++++++++++++++++++++++++++++
+                                                      +
+                                 ;.; G                +
+                                ,,:iG G               +
+                               ,tC   , C              +
+                              ,fC    L  C             +
+                             ;fL     iL  G            +
+                            :fi       8   G           +
+                           if          Coio           +
+                          if                          +
+                        .1L                           +
+                       :fL                            +
+            t1it,     :LL                             +
+           LGf::C;1t .tL                              +
+          tG1::;;;G;:1f;                              +
+         GL,;;;;;iiii:8G:if                           +
+         t:iiiiiiiiiiii;;;:ii                         +
+           tt;i;iii;;;i;;iLGi                         +
+              ;fi;;;;;;;;GG,                          +
+                  ff:;:;GL                            +
+                      LL1                             +
+                            ;                         +
+                            @t          GG            +
+                            @t                        +
+   f@@8   0@@  @@C          @t         t@@ to    or   +
+   G8@@: t8@@   G:   L0L    @t ;0 L0C   18  0GGGrr    +
+   8C @@ @ @@   @L @@   @@  @t 1@:  @@  @@  @@        +
+   @L  @@  @@   @L @8   0@  @t 1@.  @@  @@  @@        +
+  C@@:    ,@@@  @L  @@f@@  0@@ @@0 .@@1i@@ t@@        +
+                @L                                    +
+                @L                                    +
+             oGGG                                     +
+                                                      +
++++++++++++++++++++++++++++++++++++++++++++++++++++++++`


	fmt.Println(str)

}