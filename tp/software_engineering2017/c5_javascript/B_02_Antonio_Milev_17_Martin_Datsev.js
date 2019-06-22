 class Vector {
     constructor(x = 0, y = 0) {
         this.x = x;
         this.y = y;
     }
     subtract(v) {
         if (v instanceof Vector) {
             return new Vector(this.x - v.x, this.y - v.y)
         } else {
             return new Vector(this.x - v, this.y - v)
         }
     }
     multiply(v) {
         if (v instanceof Vector) {
             return new Vector(this.x * v.x, this.y * v.y)
         } else {
             return new Vector(this.x * v, this.y * v)
         }
     }
     dot(v) {
         return this.x * v.x + this.y * v.y;
     }
     cross(v) {
         return this.x * v.y - this.y * v.x
     }
     lengthSq() {
         return this.dot(this);
     }
     normalize() {
         return this.divide(this.length());
     }
     length() {
         return Math.sqrt(this.dot(this));
     }
     draw(ctx, x = 0, y = 0) {
         ctx.save();
         ctx.beginPath();
         ctx.moveTo(x, y);
         ctx.lineTo(x + this.x, y + this.y);
         ctx.stroke();
         ctx.restore();
     }
 }

 class Ball {
     constructor(options = {}) {
         let {
             x,
             y,
             vy,
             vx,
             r,
             color,
             textureURL
         } = options;
         this.texture = new Image();
         this.texture.src = 'https://i.imgur.com/uIPlAEE.png';
         this.pos = new Vector(x, y);
         this.vel = new Vector(vx, vy);
         this.r = r;
         this.color = color;
         this.lastUpdate = Date.now();
     }

     draw(ctx) {
         ctx.save();

         ctx.beginPath();
         if (invincible)
             ctx.globalAlpha = 0.4;
         ctx.arc(this.pos.x, this.pos.y, this.r, 0, 2 * Math.PI);
         ctx.fillStyle = this.color;
         ctx.fill();
         ctx.drawImage(this.texture, this.pos.x - this.r, this.pos.y - this.r, this.r * 2, this.r * 2);
         ctx.restore();

         var now = Date.now();
         var dt = now - this.lastUpdate;

         let newPos = {
             x: this.pos.x + this.vel.x * dt,
             y: this.pos.y + this.vel.y * dt
         };
         if (newPos.y > ctx.canvas.height || newPos.y < 0) {
             //this.pos.y = ctx.canvas.height - this.r;
             this.vel.y = -this.vel.y;
             return;
         }
         if (newPos.x > ctx.canvas.width || newPos.x < 0) {
             //this.pos.x = ctx.canvas.width; - this.r;
             this.vel.x = -this.vel.x;
             return;
         }
         this.pos.x = newPos.x;
         this.pos.y = newPos.y;

         this.lastUpdate = now;


     }

     // collides(ball2) {
     //     return (this.pos.x - ball2.pos.x) ** 2 + (this.pos.y - ball2.pos.y) ** 2 <=
     //         (this.r + ball2.r) ** 2;
     // }
 }

 function randomColor() {
     return '#' + Math.floor(Math.random() * 16777215).toString(16);
 }



 let mx, my;
 let lives;
 let score;
 let highScore = 0;
 let balls = [];
 let invincible;
 let invTimer;

 function setInvincible(timeout = 1000) {
     invincible = true;
     clearTimeout(invTimer);
     invTimer = setTimeout(_ => invincible = false, timeout);
 }

 //var ball = new Image();
 //ball.src = 'ball.png';
 let canvas = document.getElementById('canvas');
 let ctx = canvas.getContext('2d');

 function setup() {
     lives = 3;
     score = 0;
     for (let i = 0; i < 10; i++) {
         //do {
         balls[i] = randomBall();
         //} while (balls.some((b, i) => b.collides(balls[i])));
     }
     setInvincible();
 }
 setup();
 window.requestAnimationFrame(draw);

 //let prevballs = [];

 function randomBall() {
     return new Ball({
         vy: (.5 - Math.random()) * .5,
         vx: (.5 - Math.random()) * .5,
         r: Math.random() * 60 + 15,
         x: Math.random() * canvas.width,
         y: Math.random() * canvas.height,
         color: randomColor()
     })
 }



 // balls = [
 //     new Ball({
 //         vy: -.2,
 //         vx: 0.01,
 //         r: 25,
 //         x: 300,
 //         y: 400,
 //         color: "red"
 //     }),
 //     new Ball({
 //         vy: 0.01,
 //         vx: 0.01,
 //         r: 25,
 //         x: 300,
 //         y: 100,
 //         color: "red"
 //     }),

 //     new Ball({
 //         vy: 0,
 //         vx: .2,
 //         r: 25,
 //         x: 100,
 //         y: 100,
 //         color: "red"
 //     }),
 //     new Ball({
 //         vy: -.2,
 //         vx: 0,
 //         r: 25,
 //         x: 500,
 //         y: 100,
 //         color: "red"
 //     }),
 // ]

 /*function distance(v1, v2)
 {
     return Math.sqrt((v1.x - v2.x) ** 2 + (v1.y - v2.y) ** 2)
 }

 function hack()
 {
     for (var obj1 in balls) {
         for (var obj2 in balls) {
             if (obj1 !== obj2 &&
                 distance(balls[obj1].pos, balls[obj2].pos) < balls[obj1].r + balls[obj2].r) {
                 var theta = Math.atan2((balls[obj1].pos.y - balls[obj2].pos.y), (balls[obj1].pos.x - balls[obj2].pos.x));
                 var overlap = balls[obj1].r + balls[obj2].r - distance(balls[obj1].pos, balls[obj2].pos);
                 balls[obj1].pos.x += overlap * Math.cos(theta);
                 balls[obj1].pos.y += overlap * Math.sin(theta);
             }
         }
     }
 }*/

 function mouseOnBall(b) {
     return (mx - b.pos.x) ** 2 + (my - b.pos.y) ** 2 <= b.r ** 2
 }

 setInterval(function newBall() {
     score += 10;
     let newBall;
     do {
         newBall = randomBall();
     } while (mouseOnBall(newBall));
     balls.push(newBall);
 }, 5000)

 setInterval(function incScore() {
     score++;
 }, 100)

 function gameOver() {
     balls = [];
     if (score > highScore)
         highScore = score;
     console.log("u ded");
     setup();
 }

 function checkMouse() {
     if (invincible) return;
     if (my > ctx.canvas.height || my < 0 || mx > ctx.canvas.width || mx < 0) {
         gameOver();
     }

     if (balls.some(b => mouseOnBall(b))) {
         console.log(lives);
         if (--lives == 0)
             gameOver();
         setInvincible();
     }
 }

 function draw(e) {
     ctx.fillStyle = `black`;
     ctx.fillRect(0, 0, ctx.canvas.width, ctx.canvas.height);
     //let newposs = [];
     //hack();
     // for (let i = 0; i < balls.length; i++) {
     //     for (let j = 0; j < balls.length; j++) {
     //         if (j == i) continue;
     //         if (balls[i].collides(balls[j])) {
     //             console.log(i, j);
     //             let v1 = balls[i].vel,
     //                 v2 = balls[j].vel,
     //                 m1 = balls[i].r,
     //                 m2 = balls[j].r,
     //                 c1 = balls[i].pos,
     //                 c2 = balls[j].pos,
     //                 r1 = balls[i].r,
     //                 r2 = balls[j].r,
     //                 x1 = balls[i].pos.x,
     //                 x2 = balls[j].pos.x,
     //                 y1 = balls[i].pos.y,
     //                 y2 = balls[j].pos.y;

     //             let vdiff = v1.subtract(v2);
     //             let cdiff = c1.subtract(c2);
     //             let num = 2 * m2 * (vdiff).dot(cdiff);
     //             let den = ((m1 + m2) * (cdiff.lengthSq()));
     //             let subtracted = cdiff.multiply(num / den);
     //             balls[i].vel = v1.subtract(subtracted);

     //             vdiff = v2.subtract(v1);
     //             cdiff = c2.subtract(c1);
     //             num = 2 * m1 * (vdiff).dot(cdiff);
     //             den = ((m1 + m2) * (cdiff.lengthSq()));
     //             subtracted = cdiff.multiply(num / den);
     //             balls[j].vel = v2.subtract(subtracted);
     //             balls[i].pos.x = prevballs[i].x;
     //             balls[j].pos.y = prevballs[j].y;
     //             //balls[i].vel.multiply(100).draw(ctx, x1, y1);
     //             //let p1 = new Vector(Math.sqrt((r1 * x2) ** 2 / (x2 ** 2 + y2 ** 2)),
     //             //    Math.sqrt((r1 * y2) ** 2 / (y2 ** 2 + x2 ** 2)));
     //             //let p2 = new Vector(Math.sqrt((r2 * x1) ** 2 / (x1 ** 2 + y1 ** 2)),
     //             //    Math.sqrt((r2 * y1) ** 2 / (y1 ** 2 + x1 ** 2)));
     //             //p1.subtract(p2).draw(ctx, x1 + p1.x, y1 + p1.y);
     //             //p2.subtract(p1).draw(ctx, x2 + p2.x, y2 + p2.y);
     //             //newposs[i] = p2.subtract(p1).multiply(.5);
     //             //newposs[i].multiply(10).draw(ctx, x1, y1);
     //             //balls[j].pos.x += p1.subtract(p2).x / 2;
     //             //balls[j].pos.y += p1.subtract(p2).y / 2;

     //         }
     //     }
     // }
     // balls.forEach((b, i) => prevballs[i] = {
     //     x: b.pos.x,
     //     y: b.pos.y
     // })
     // //for (let i = 0; i < balls.length; i++) {
     // //    if (newposs[i]) {
     // //        balls[i].pos.x += newposs[i].x;
     // //        balls[i].pos.y += newposs[i].y;
     // //    }
     // //}

     balls.forEach(b => b.draw(ctx));
     ctx.font = "30px Comic Sans MS";
     ctx.fillStyle = "cyan";
     ctx.fillText(`Score: ${score}`, 30, 30);
     ctx.fillText(`Lives: ${lives}`, 30, 60);
     ctx.fillText(`HighScore: ${highScore}`, 30, 90);
     window.requestAnimationFrame(draw);
     checkMouse();
 }

 // window.addEventListener("click", e => {
 //     [mx, my] = getMousePos(canvas, e);
 //     if ((mx - ball.x) ** 2 + (my - ball.y) ** 2 <= ball.r ** 2) {
 //         ball.x = Math.random() * canvas.width, ball.y = Math.random() * canvas.height, ball.vx *= 1.1, ball.vy *= 1.1
 //         score++;
 //         ball.r *= 0.8;
 //         imgSize *= 0.8;
 //     } else {
 //         lives--;
 //         if (lives == 0) {
 //             alert("Nqkoi da pomaga");
 //         }
 //     }
 //     console.log(`lives: ${lives}, score ${score}`);
 // });

 window.addEventListener("mousemove", e => {
     [mx, my] = getMousePos(canvas, e);
 });

 function getMousePos(canvas, evt) {
     var rect = canvas.getBoundingClientRect();
     return [
         evt.clientX - rect.left,
         evt.clientY - rect.top
     ];
 }
