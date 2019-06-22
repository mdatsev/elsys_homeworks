{
    Number.prototype.clamp = function (min, max) {
        return Math.min(Math.max(this, min), max);
    }

    Number.prototype.map = function (in_min, in_max, out_min, out_max) {
        return (this - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
    }

    let mouseEvent = {
        clientX: -9999,
        clientY: -9999
    };

    window.addEventListener("mousemove", e => mouseEvent = e);

    function getMousePos(canvas, evt) {
        var rect = canvas.getBoundingClientRect();
        return [
            evt.clientX - rect.left,
            evt.clientY - rect.top
        ];
    }

    let canvas = document.getElementById("about-canvas");
    let ctx = canvas.getContext("2d");
    canvas.width = document.body.clientWidth;
    canvas.height = window.innerHeight;
    var img = new Image();

    let hCount = 6;
    let vCount = 5;
    let xspread = 2000;
    let yspread = 000;
    let speed = 1 - 0.10;
    let angleSpread = 0;
    let epsilon = 0.001;
    let points = [];
    let eq = {
        a: 0.8,
        b: 0,
        c: 400000,
        d: 0,
        e: 1,
        f: .95,
        g: 2,
        h: 0,
        i: 1
    }
    const signedRnd = _ => 0.5 - Math.random();

    function randomize() {
        hCount = 2 + Math.floor(Math.random() * 20)
        vCount = 2 + Math.floor(Math.random() * 20)
        xspread = Math.random() * 10000
        yspread = Math.random() * 10000
        speed = 0.66 + Math.random() * 0.33
        angleSpread = Math.random() * 300
        /*eq = {
            a: Math.random(),
            b: Math.random(),
            c: Math.random() * 800000,
            d: Math.random(),
            e: Math.random(),
            f: Math.random(),
            g: Math.random() * 4,
            h: Math.random(),
            i: Math.random()
        }*/
    }

    function generate(sizex = 1, sizey = 1) {
        for (let i = 0; i < vCount; i++) {
            points[i] = [];
            for (let j = 0; j < hCount; j++) {
                points[i][j] = {
                    x: sizex / hCount * (j + (j == 0 ?
                        0 :
                        j == hCount - 1 ?
                        1 :
                        Math.random())),
                    y: sizey / vCount * (i + (i == 0 ?
                        0 :
                        i == vCount - 1 ?
                        1 :
                        Math.random())),
                    offset1x: signedRnd() * xspread,
                    offset1y: signedRnd() * yspread,
                    offset2x: signedRnd() * xspread,
                    offset2y: signedRnd() * yspread,
                    angle1: signedRnd() * angleSpread,
                    angle2: signedRnd() * angleSpread
                };
            }
        }
    }

    function execute() {
        canvas.addEventListener("click", () => (randomize(), generate(img.width, img.height)));
        generate();
        for (let i = 0; i < vCount; i++) {
            for (let j = 0; j < hCount; j++) {
                points[i][j].x *= img.width;
                points[i][j].y *= img.height;
            }
        }
        const centerx = canvas.width / 2 - img.width / 2;
        const centery = canvas.height / 2 - img.height / 2;
        ctx.setTransform(1, 0, 0, 1, 0, 0);
        ctx.translate(centerx, centery)



        function drawSegment(image, p1, p2, p3, offsetx, offsety, angle, scale, center) {
            ctx.save();
            if (offsetx || offsety) {
                ctx.translate(offsetx, offsety);
            }

            if (angle || scale != 1) {

                ctx.translate(center.x, center.y)
                ctx.rotate(angle);
                ctx.scale(scale, scale);
                ctx.translate(-center.x, -center.y)
            }

            ctx.beginPath();
            ctx.moveTo(p1.x, p1.y);
            ctx.lineTo(p2.x, p2.y);
            ctx.lineTo(p3.x, p3.y);
            ctx.clip();
            ctx.drawImage(image, 0, 0);
            ctx.restore();

        }

        function integrate(p1) {
            [
                "offset1x",
                "offset1y",
                "offset2x",
                "offset2y",
                "angle1",
                "angle2"
            ].forEach(p => p1[p] *= Math.abs(p1[p]) > epsilon ? speed : 0)
        }

        function draw() {
            let [mx, my] = getMousePos(canvas, mouseEvent);
            let done = true;
            ctx.clearRect(-centerx, -centery, canvas.width, canvas.height);
            for (let i = 0; i < vCount - 1; i++) {
                for (let j = 0; j < hCount - 1; j++) {
                    const p1 = points[i][j];
                    const p2 = points[i + 1][j];
                    const p3 = points[i][j + 1];
                    const p4 = points[i + 1][j + 1];
                    center1 = {
                        x: (p1.x + p2.x + p3.x) / 3,
                        y: (p1.y + p2.y + p3.y) / 3
                    };
                    center2 = {
                        x: (p2.x + p3.x + p4.x) / 3,
                        y: (p2.y + p3.y + p4.y) / 3
                    };
                    let distSq1 = Math.pow(mx - centerx - center1.x, 2) + Math.pow(my - centery - center1.y, 2);
                    let distSq2 = Math.pow(mx - centerx - center2.x, 2) + Math.pow(my - centery - center2.y, 2);
                    //debuga += distSq;
                    //debugc++;

                    let scale1 = Math.pow(eq.a * distSq1.map(eq.b, eq.c, eq.d, eq.e) + eq.f, eq.g).clamp(eq.h, eq.i); //NO TOUCH ME
                    let scale2 = Math.pow(eq.a * distSq2.map(eq.b, eq.c, eq.d, eq.e) + eq.f, eq.g).clamp(eq.h, eq.i); //NO TOUCH ME
                    if (1 < epsilon) scale = 1;
                    drawSegment(img, p1, p2, p3, p1.offset1x, p1.offset1y, p1.angle1, scale1, center1);
                    drawSegment(img, p2, p3, p4, p1.offset2x, p1.offset2y, p1.angle2, scale2, center2);
                    integrate(p1);
                }
            }
            window.requestAnimationFrame(draw);
        }
        window.requestAnimationFrame(draw);
    }
    img.addEventListener('load', execute, false);
    img.src = 'about.png';
}