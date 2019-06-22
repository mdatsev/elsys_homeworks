 //bonus little minigame for noobs
    var canvas = document.getElementById('canvas');
    var ctx = canvas.getContext('2d');

    var player = {
        lives: 3,
        score: 0
    }

    var ball = {
        x: 100,
        y: 100,
        vx: 4,
        vy: 2,
        radius: 70,
        color: 'blue',
        draw: function () {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2, true);
            ctx.closePath();
            ctx.fillStyle = this.color;
            ctx.fill();
        }
    };

    var quotes = ["",
                    "You know you shouldn't even try?",
                    "Just click anywhere you want...",
                    "Why do you keep doing this?",
                    "Stop!",
                    "There's no point in this!",
                    "You're quite stubborn aren't you?",
                    "Okay. One more right click and you're dead!",
                    "I'm done..."];
    var quoteIndex = 0;

    function init() {
        canvas.addEventListener("click", clickBall, false);
        window.requestAnimationFrame(draw);
    }

    function draw() {
        ctx.clearRect(0, 0, canvas.width, canvas.height);
        ball.draw();
        ball.x += ball.vx;
        ball.y += ball.vy;
        if (ball.y + ball.vy + ball.radius > canvas.height || ball.y + ball.vy - ball.radius < 0) {
            ball.vy = -ball.vy;
        }
        if (ball.x + ball.vx + ball.radius > canvas.width || ball.x + ball.vx - ball.radius < 0) {
            ball.vx = -ball.vx;
        }
        ctx.font = "30px Comic Sans MS";
        ctx.fillStyle = "black";
        ctx.fillText(`Score: ${player.score}`,30,30);
        ctx.fillText(`Lives: ${player.lives}`,30,60);

        ctx.fillText(`${quotes[quoteIndex]}`,150,200);
        window.requestAnimationFrame(draw);
    }

    function clickBall(event) {
        var x = event.x - canvas.offsetLeft;
        var y = event.y - canvas.offsetTop;
        if((ball.x - x) ** 2 + (ball.y - y) ** 2 < ball.radius ** 2) {
            //ctx.fillText(`${quotes[quoteIndex]}`, 400, 300);
            quoteIndex++;
            if(quoteIndex == quotes.length - 1) {
                gameOver();
            }
            //console.log("got em");
        }
        ball.x = x;
        ball.y = y;
        player.score += 10;
        ball.radius *= 0.9;
        //console.log(x, y , ball.x, ball.y);
    }

    function gameOver() {
        alert("Told you");
        player.score = 0;
        player.lives = 3;
        ball.x = 100;
        ball.y = 100;
        ball.vx = 4;
        ball.vy = 2;
        ball.radius = 70; 
        ball.draw();
    }

    function getRandom(min, max) {
        return Math.floor(Math.random() * (max - min) ) + min;
    }
