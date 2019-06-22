function game2() {
	var c = document.getElementById("game-2-canvas");
	var ctx = c.getContext("2d");
	var width = c.width;
	var height = c.height;
	var G = 0.1;
	var fillRectAlpha = 1;
	var spawnTime = 1000,
		score = 0;
	var scoreText = document.getElementById("score");
	var numberOfBalls = 1;
	var dead = false;
	var balls = [];
	var spawners = [];

	function random(min, max) {
		var num = Math.floor(Math.random() * (max - min)) + min;
		return num;
	}

	function Shape(x, y, velX, velY) {
		this.x = x;
		this.y = y;
		this.velX = velX;
		this.velY = velY;
	}


	function Ball(x, y, velX, velY, coefV, radius, lives, pathToImage, dead) {
		Shape.call(this, x, y, velX, velY);
		this.coefV = coefV;
		this.radius = radius;
		this.lives = lives;
		this.pathToImage = pathToImage;
		this.dead = dead;
	}


	function Spawner(x, y, velX, velY, width, height, spawnInterval, ballsCount, pathToImage) {
		Shape.call(this, x, y, velX, velY);
		this.width = width;
		this.height = height;
		this.spawnInterval = spawnInterval;
		this.ballsCount = ballsCount;
		this.pathToImage = pathToImage;
	}

	Ball.prototype = Object.create(Shape.prototype)
	Ball.prototype.constructor = Ball;
	Spawner.prototype = Object.create(Shape.prototype)
	Spawner.prototype.constructor = Spawner;

	Ball.prototype.draw = function () {
		var thumbImg = new Image();
		thumbImg.src = this.pathToImage;
		ctx.drawImage(thumbImg, this.x, this.y, this.radius, this.radius);
	}

	Ball.prototype.update = function () {
		this.velY = this.velY == 0 ? 0 : this.velY += G;
		this.x += this.velX;
		this.y += this.velY;
		if ((this.x + this.radius + this.velX) >= width || (this.x - this.radius + this.velX) <= 0) {
			this.velX = -this.velX;
			//this.velX *= this.coefV;
			;;
		}
		if ((this.y + this.radius + this.velY) >= height || (this.y - this.radius + this.velY) <= 0) {
			this.velY = -this.velY;
			this.lives--;
			//this.velY *= -this.coefV;
			;;
		}
		if (!this.lives) {
			alert("Game over");
			dead = true;
		}
	}

	Spawner.prototype.draw = function () {
		var thumbImg = new Image();
		thumbImg.src = this.pathToImage;
		ctx.drawImage(thumbImg, this.x, this.y, this.width, this.height);

	}

	Spawner.prototype.update = function () {
		this.spawnInterval = this.spawnInterval == 500 ? 500 : this.spawnInterval -= 100;
		//this.ballsCount += 1;
	}

	Spawner.prototype.spawn = function () {
		var t = this;;;
		//for(var i = 0; i < t.ballsCount; i++) {
		//	setTimeout(function(){balls.push(new Ball(t.x, t.y, random(1, 5) + 0.5, random(-5, 5) + 0.5, 0.9, 50, 1, "https://i.imgur.com/uIPlAEE.png", false))}, t.spawnInterval * (i + 1));
		//}	
		balls.push(new Ball(t.x + t.width / 2, t.y + t.height / 2, random(-5, 5) + 0.5, random(1, 5) + 0.5, 0.9, 50, 10, "https://i.imgur.com/uIPlAEE.png", false));
	}


	function init() {
		for (var i = 0; i < 4; i++) {
			spawners.push(new Spawner(100 + i * 200, 50, 0, 0, 100, 100, spawnTime, numberOfBalls, "https://i.imgur.com/uIPlAEE.png"));
			//setTimeout(spawners[i].spawn(), spawners[i].spawnInterval);
		}
		c.addEventListener('click', function (evt) {
			var rect = c.getBoundingClientRect();
			let e = {
				x: evt.clientX - rect.left,
				y: evt.clientY - rect.top
			}
			for (var i = 0; i < balls.length; i++) {
				if ((e.x < balls[i].x + balls[i].radius && e.x > balls[i].x - balls[i].radius) &&
					(e.y < balls[i].y + balls[i].radius && e.y > balls[i].y - balls[i].radius)) {
					balls[i].dead = true;
					score += 100;
				} else {
					if (dead) {
						location.reload();
					}
				}
			}
		});
		window.requestAnimationFrame(draw);
		updateSpawners();
		spawnBalls();
		setInterval(spawnBalls, spawnTime);
		setInterval(updateSpawners, 10000);
	}

	function updateSpawners() {
		for (var i = 0; i < spawners.length; i++) {
			if (!dead) {
				spawners[i].update();
			}
		}
	}

	function spawnBalls() {
		var index = random(1, spawners.length);
		setTimeout(function () {
			spawners[index].spawn();
		}, spawners[index].spawnInterval);
	}

	function draw() {
		ctx.fillStyle = `rgba(255,255,255,${fillRectAlpha})`;
		ctx.clearRect(0, 0, width, height);
		window.onkeydown = function (e) {
			if (e.keyCode === 65) { // a
				var r = random(50, 100)
				var ball = new Ball(random(0 + r, width - r), random(0 + r, height - r), random(-5, 5) + 0.5, random(-5, 5) + 0.5, 0.9, r, 10, "https://i.imgur.com/uIPlAEE.png", false);
				balls.push(ball);
			}
			if (e.keyCode === 69) { // e
				fillRectAlpha -= 1;
				fillRectAlpha = Math.abs(fillRectAlpha);;;
			}
		}
		for (var i = 0; i < balls.length; i++) {
			if (!balls[i].dead) {
				balls[i].draw();
				if (!dead)
					balls[i].update();
			}
		}
		for (var i = 0; i < spawners.length; i++) {
			spawners[i].draw();
		}
		ctx.fillStyle = 'blue';
		ctx.fillText("Score: " + score, 20, 30);
		window.requestAnimationFrame(draw);
	}

	init();
}