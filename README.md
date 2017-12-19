# study__shader #

## 環境 ##
*	Xcode : 7.2
*	oF : 0.9.0

## add on ##

## Contents ##
### fragment distortion ###


### fragment perlinNoise  ###
水面のような表現

### fragment several image  ###
複数イメージをshaderに渡すケース。
本ケースでは、画像の他に、mask imageも渡して使用。

### fragment audio reactive  ###
fft結果を使い、円周上に揺れを表現する。
fft結果を1次元画像データとして扱っている。

### vertex  ###
球面上にofTriangle()を描画。
mouse位置でdistortionさせる。

### geometry  ###
画面一面にofLine()で描画し、これをshaderで受けてtextureを使い、起毛っぽい表現をする。

### geometry  ###
geometry shaderの動きを研究

### geometry  ###
geometry shaderの動きをさらに研究。  
ofVbo x shader:vboには一度に全ての頂点情報を格納するが、shaderは、各primitiveの描画ごとに起動される。
shader.setGeometryOutputCount( 4 );で指定するのは、1回のgeom:mainでemitするvertex数。  

## note ##






