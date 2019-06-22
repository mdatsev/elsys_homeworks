let cmds = [
    "ls",
    "cat",
    "wc",
    "grep",
    "true",
    "false",
    "pwd",
    "echo",
    "hostname",
    "ping",
    "asd"
]

let args = [
    "-la",
    "file",
    "../other",
    "/",
    "asd",
    "shell",
    "s"
]

let str = "";
for (let k = 0; k < Math.random() * 20 + 1; k++) {
    for (let i = 0; i < Math.random() * 20 + 1; i++) {
        space();
        if (k > 0) {
            str += "|";
        }
        space();
        str += cmds[Math.floor(Math.random() * cmds.length)];

        space();
        for (let j = 0; j < Math.random() * 10 + 1; j++) {
            space();
            str += args[Math.floor(Math.random() * args.length)];

        }
        space();
    }
    str += "\n";
}

function space() {
    for (let j = 0; j < Math.random() * 5 + 1; j++) {
        str += " ";
    }
}

console.log(str)