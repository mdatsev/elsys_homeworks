let quotes = [`koi master yi da si zema na yasuo tryndamere li?`,

    `ne e chesnto leblanc me izigravach!!!`,

    `az sum avto ataka!`,

    `iskam sreshtu azir a ne sreshtu krskoto`,

    `Картофените кюфтета са много нормални. Даже вкъщи са нормални защото аз често обичам да ги ям.`,

    `Как мислите това флашка или мишка е?`,

    `НЕЕЕ не е честно, ако си купя две zhonya-и мога само едната да ползвам!!! :((((`,

    `kakvo trqbva da pushna zada talkna`,

    `ti promeniqsh ugovorkata az promenqm sdelkata`,

    `ei sega idvam i idvam sled malko`,

    `kak se striimva v twich`,

    `"Абе тоско, съпротивлението измервателен апарат ли е?"
Тоско: "Амиии, не знам"`,

    `Тоско: "Имам добри основи за есето ми, имам логаритъм"
Тери: "Знаеш ли какво е логатитъм?"
Тоско: "Да...логиката.."`,

    `"nerfvat daisy veche ne si regenva krufta "
tosko: "amo to kucheto na kindred veche nqma da si regenva krufta"`,

    `"how can this video have 10 million views if there are 7 million people on earth?"
tosko: "kak ne sa li milqrda"`,

    `kris molq te pravi me
kris molq te opravi* me`,

    `Tosko:"kvo pravite" 
Toni: "kachvam si after effects" 
Tosko: "Na skyrim li?"`,

    `"Tosko, da te chakame li na serdika"
Tosko: "Ne, ne me slizaite"`
];

[].forEach.apply(document.getElementsByClassName("quote"), [q => q.onclick = () => q.innerText = `“${quotes[Math.floor(Math.random() * quotes.length)]}”`])