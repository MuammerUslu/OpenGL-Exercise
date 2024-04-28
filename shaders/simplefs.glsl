#version 330 core
out vec4 fragColor;

in vec3 ourColor; // Girdi renk verisi

uniform float windowHeight; // Uniform değişken

void main()
{
    // Kırmızı, yeşil ve mavi bileşenler
    float red = 1.0;
    float green = 1.0;
    float blue = 1.0;

    // Vertex'in y koordinatına bağlı olarak renk karışımı hesaplama
    float mixFactor = gl_FragCoord.y / windowHeight; // Varsayılan pencere yüksekliği için normalleme yapılabilir

    // Renkleri karıştırma
    red = mix(red, ourColor.r, mixFactor);
    green = mix(green, ourColor.g, mixFactor);
    blue = mix(blue, ourColor.b, mixFactor);

    // Son renk değerini kullanarak çıktıyı oluştur
    //fragColor = vec4(red, green, blue, 1.0);

    //fragColor = vec4(ourColor.r, ourColor.g, ourColor.b, 1.0);

    //if(gl_FragCoord.x < 400)
    //    fragColor = vec4(1.0, 0.0, 0.0, 1.0);
    //else
    //    fragColor = vec4(0.0, 1.0, 0.0, 1.0);

    fragColor = vec4(0.0, 0.0, mixFactor, 1.0);

}