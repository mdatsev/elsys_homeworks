function game3() {
    texture = new Image();
    texture.src = 'https://i.imgur.com/uIPlAEE.png'

    canvas = document.querySelector('#game-3-canvas')
    canvas.width = 1000
    canvas.height = 1000
    direction = "right"
    c = canvas.getContext('2d')
    var x = 20;
    var y = 129;
    var r = 20;
    score = 0;
    //document.documentElement.style.overflow = 'hidden';
    setup();
    var level = 1;

    function setup() {
        c.beginPath();
        c.moveTo(10, 100);
        c.lineTo(10, 600);
        c.stroke();
        c.beginPath();
        c.moveTo(700, 100);
        c.lineTo(700, 600);
        c.stroke();
    }

    function clear() {
        c.clearRect(0, 0, canvas.width, canvas.height)
    }
    spawn();

    function spawn() {
        clear();
        setup();
        level++;
        c.beginPath();

        y = Math.floor(Math.random() * (600 - 100 + 1)) + 100
        x = 0;
        r = Math.floor(Math.random() * (60 - 20 + 1)) + 20
        c.arc(x, y, r, 0, 2 * Math.PI);
        c.fillStyle = getRandomColor();
        c.fill();
        c.stroke();
        animation();
    }

    function animation() {
        function move() {
            c.clearRect(0, 0, canvas.width, canvas.height)
            setup();
            c.font = "30px Verdana";
            c.fillText("Score:" + score, 10, 90);
            c.beginPath();

            if (x > 700) {
                score = 0
                level = 1
                spawn();
                return;
            }
            c.arc(x, y, r, 0, 2 * Math.PI);
            c.fill();
            c.stroke();
            c.drawImage(this.texture, x - r, y - r, r * 2, r * 2);
            x += level;
            requestId = requestAnimationFrame(move);
        }
        requestId = requestAnimationFrame(move);
    }

    function check(evt) {
        var rect = canvas.getBoundingClientRect();
        let e = {
            x: evt.clientX - rect.left,
            y: evt.clientY - rect.top
        }
        if ((e.x < x + r && e.x > x - r) && (e.y < y + r && e.y > y - r)) {
            spawn();
            score++;
        }

    }
    window.addEventListener('click', check)

    function getRandomColor() {
        var letters = '0123456789ABCDEF';
        var color = '#';
        for (var i = 0; i < 6; i++) {
            color += letters[Math.floor(Math.random() * 16)];
        }
        return color;
    }
}