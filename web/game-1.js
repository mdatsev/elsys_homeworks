function game1() {

    var canvas = document.getElementById('game-1-canvas');
    if (canvas.getContext) {
        var ctx = canvas.getContext('2d');
        ctx.font = "30px Arial";
    }
    ctx.globalAlpha = 0.6;

    var raf;
    var is_corect_click = 0;
    var lives = 3;
    var score = 0;
    var bonus = 80;
    var balls = new Array;

    function draw() {
        ctx.fillStyle = 'white';
        ctx.fillRect(0, 0, canvas.width, canvas.height);
        for (var i = 0; i < balls.length; i++) {
            balls[i].draw();
            balls[i].x += balls[i].vx;
            balls[i].y += balls[i].vy;

            if (balls[i].y + balls[i].radius + balls[i].vy > canvas.height ||
                balls[i].y - balls[i].radius + balls[i].vy < 0) {
                balls[i].vy = -balls[i].vy;
            }

            if (balls[i].x + balls[i].radius + balls[i].vx > canvas.width ||
                balls[i].x - balls[i].radius + balls[i].vx < 0) {
                balls[i].vx = -balls[i].vx;
            }
        }
        ctx.fillStyle = 'blue';
        ctx.fillText("Score: " + score, 20, 30);
        ctx.fillText("Lives: " + lives, 20, 60);

        raf = window.requestAnimationFrame(draw);
    };

    var ball = {
        x: 100,
        y: 100,
        vx: 5,
        vy: 1,
        radius: 100,
        curr_color: 'blue',
        texture: new Image(),
        is_mouse_over: function (x, y) {
            return ((this.x - radius) < x < (this.x + radius)) &&
                ((this.y - radius) < y < (this.y + radius));
        },
        draw: function () {
            ctx.beginPath();
            ctx.arc(this.x, this.y, this.radius, 0, Math.PI * 2, true);
            ctx.closePath();
            ctx.fillStyle = this.curr_color;
            ctx.fill();
            ctx.drawImage(this.texture, this.x - this.radius, this.y - this.radius, this.radius * 2, this.radius * 2);
        }
    };
    ball.texture.src = 'https://i.imgur.com/uIPlAEE.png'
    balls.push(ball);

    canvas.addEventListener('click', function (evt) {
        is_corect_click = 0;
        var rect = canvas.getBoundingClientRect();
        let e = {
            x: evt.clientX - rect.left,
            y: evt.clientY - rect.top
        }
        for (var i = 0; i < balls.length; i++) {
            if ((e.x - 10 < balls[i].x + balls[i].radius && e.x - 10 > balls[i].x - balls[i].radius) &&
                (e.y - 10 < balls[i].y + balls[i].radius && e.y - 10 > balls[i].y - balls[i].radius)) {
                var new_ball = balls[i];
                balls.splice(i, 1);
                new_ball.radius *= 0.7;
                balls.push(Object.assign({}, new_ball));
                balls.push(Object.assign({}, new_ball));

                balls[balls.length - 2].x = Math.floor(Math.random() * 600) + 100;
                balls[balls.length - 2].y = Math.floor(Math.random() * 400) + 100;
                balls[balls.length - 2].vx = Math.floor(Math.random() * 5) + 1;
                balls[balls.length - 2].vy = Math.floor(Math.random() * 5) + 1;
                balls[balls.length - 2].curr_color = "#" + Math.floor(Math.random() * 16777215).toString(16);

                balls[balls.length - 1].x = Math.floor(Math.random() * 600) + 100;
                balls[balls.length - 1].y = Math.floor(Math.random() * 400) + 100;
                balls[balls.length - 1].vx = Math.floor(Math.random() * 5) + 1;
                balls[balls.length - 1].vy = Math.floor(Math.random() * 5) + 1;
                balls[balls.length - 1].curr_color = "#" + Math.floor(Math.random() * 16777215).toString(16);


                if (e.x == ball.x && e.y == ball.y) {
                    score += 500;
                } else {
                    bonus += 20;
                    score += bonus;
                }

                is_corect_click = 1;
                break;
            }
        }
        if (!is_corect_click) {
            lives--;

            if (lives < 1) {
                alert("You died");
                location.reload();
            }
        }
    });
    draw();

}