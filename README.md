# A Neural Network Written Entirely in C

A 'built from scratch' digit recognizer that trains on 60,000 handwritten images and reaches 97%+ accuracy 
no frameworks, no libraries, just arrays and loops.

---

## What Is This?

Imagine you write the number "7" on a piece of paper. You know it's a 7 because your brain has seen thousands of 7s in your lifetime and learned what they look like. This project does the same thing — but with a computer program written in C.

The program looks at 60,000 pictures of handwritten numbers (0 through 9), studies them, and teaches itself to recognize which number is which. After about 2 minutes of training, it can look at a brand new handwritten number it has never seen before and correctly guess what it is about 97 out of 100 times.

The cool part? The entire thing is built from scratch. No pre-built AI tools, no machine learning libraries, no shortcuts. Just basic math operations (addition, multiplication, and a few simple functions) written in plain C code.

There's also a drawing app where you can draw a number with your mouse and watch the program guess what you drew in real time.

---

## How Does It Actually Work?

### Think of It Like a Factory Assembly Line

Imagine a factory where a product moves through three stations. At each station, workers inspect the product and pass along notes to the next station. By the end, the last station makes a final decision.

That's basically what this neural network does, except the "product" is a picture of a handwritten number, the "stations" are layers of the network, and the "final decision" is which digit (0–9) the picture most likely shows.

### The Three Stations (Layers)

**Station 1 — The Input (784 workers)**

Each handwritten number is a tiny 28×28 pixel image. That's 784 individual dots, each one a shade from pure black to pure white. We line up all 784 dots in a single row — that's our input. Each "worker" at this station is responsible for one dot. They don't do any thinking — they just pass the brightness of their dot to the next station.

**Station 2 — The Hidden Layer (128 workers)**

This is where the magic happens. Each of the 128 workers looks at ALL 784 dots from Station 1. But here's the key — each worker pays different amounts of attention to different dots. One worker might focus heavily on the top-left corner of the image (useful for detecting the curve at the top of a "2"), while another might focus on the center (useful for detecting the cross in a "4").

How much attention each worker pays to each dot is controlled by a "weight" — a number that starts random and gets refined during training. Each worker multiplies every dot by its corresponding weight, adds everything up, and then applies a simple rule: if the total is positive, pass it along. If it's negative, send a zero instead. This rule is called "ReLU" and it's surprisingly important — without it, the network could only learn straight-line patterns, never curves.

**Station 3 — The Output (10 workers)**

There are exactly 10 workers here — one for each possible digit (0 through 9). Each one looks at what the 128 hidden workers produced and computes a score. Then all 10 scores get converted into probabilities that add up to 100%. If the "7" worker has the highest probability, the network's answer is "7."

The conversion from scores to probabilities is done by a function called "softmax." It amplifies the differences — if one score is even slightly higher than the rest, softmax makes its probability much higher, giving the network a confident answer.

### The Numbers Behind It

The network has a total of 109,386 adjustable numbers (called "parameters"):
- 100,352 weights connecting Station 1 to Station 2 (784 × 128)
- 128 biases in Station 2 (one per worker)
- 1,280 weights connecting Station 2 to Station 3 (128 × 10)
- 10 biases in Station 3 (one per worker)

Every single one of these 109,386 numbers starts as a small random value and gets gradually refined during training until the network makes accurate predictions.

---

## How Does It Learn?

### The Training Loop

Learning happens in a cycle that repeats millions of times:

**Step 1 — Make a guess.** Feed a handwritten image through the three stations and get a prediction. At the start, the prediction is essentially random because the weights are random.

**Step 2 — Measure how wrong it was.** Compare the guess to the correct answer. If the image was a "7" but the network said "3" with 80% confidence, that's very wrong. A math formula called "cross-entropy loss" puts a number on how wrong the prediction was — higher numbers mean worse predictions.

**Step 3 — Figure out who's responsible.** This is the clever part, called "backpropagation." Starting from the final answer, the program works backwards through every station asking: "how much did each weight contribute to this mistake?" It computes a "gradient" for each of the 109,386 weights — a number that says "if you increase this weight a tiny bit, the error goes up (or down) by this much."

Think of it like standing on a hilly landscape in thick fog. You can't see the valley, but you can feel which direction the ground slopes under your feet. The gradient is that slope — it tells you which direction is downhill.

**Step 4 — Adjust the weights.** Every weight gets nudged a tiny amount in the direction that would reduce the error. Weights that contributed a lot to the mistake get adjusted more. Weights that barely mattered get adjusted less. This nudging is called "gradient descent" — you're descending the hill toward the valley of low error.

**Step 5 — Repeat.** Do this for another image. And another. And another. After seeing thousands of images, the weights gradually organize themselves into a pattern that correctly recognizes digits.

### The Three Control Knobs

Three settings control how training works:

**Learning Rate (set to 0.1)** — How big each adjustment step is. Think of it like walking downhill: too big a stride and you overshoot the valley and end up on the other side. Too small and you'll be walking all night. 0.1 is a good middle ground for this project.

**Batch Size (set to 32)** — How many images the program looks at before making one adjustment. Rather than adjusting weights after every single image (which would be jittery and erratic) or after all 60,000 images (which would be slow), it looks at 32 images, averages out what it learned, and makes one smooth adjustment. Think of it like asking 32 people for directions instead of just one — you get a more reliable answer.

**Epochs (set to 20)** — How many times the program goes through all 60,000 training images. One pass through the full set is one "epoch." It's like studying a textbook: reading it once helps, but you need several passes before the material really sinks in. By epoch 20, the network has seen each image 20 times and has had plenty of opportunity to refine its weights.

### What Training Looks Like

Here's actual output from training this network:

```
Epoch  1 | Accuracy: 94.25%
Epoch  2 | Accuracy: 96.03%
Epoch  3 | Accuracy: 96.66%
Epoch  5 | Accuracy: 97.24%
Epoch 10 | Accuracy: 97.69%
Epoch 15 | Accuracy: 97.75%
Epoch 20 | Accuracy: 97.80%
```

After just one pass through the data, it's already right 94% of the time. By epoch 20, it's nearing 98%. That means out of 10,000 test images it has never seen before, it only gets about 200 wrong.

### By the Numbers

With 60,000 training images, 20 epochs, and a batch size of 32:
- **1,875 batches per epoch** (60,000 ÷ 32)
- **37,500 total weight updates** (1,875 × 20)
- **109,386 weights adjusted per update**
- That's over **4 billion** individual math operations during training

And it all runs in about 2 minutes on a regular computer.

---

## What's in the Code?

The entire neural network fits in a single file called `nn.c`. Here's what each piece does:

**`init_weights()`** — Sets all 109,386 weights to small random starting values. The randomness is carefully scaled (using a technique called "He initialization") so that signals don't get too big or too small as they pass through the network.

**`forward()`** — Takes one image and runs it through all three stations. This is the "thinking" step — the network produces a prediction. The results are saved because the learning step needs them.

**`backward()`** — The learning step. Starting from the prediction error, it works backwards through the network figuring out how much each weight contributed to the mistake. It computes a gradient (direction to adjust) for every single weight.

**`update()`** — Takes all the gradients computed by `backward()` and actually nudges the weights. This is where the network gets a tiny bit smarter after each batch of images.

**`load_mnist()`** — Reads the training data from files. The MNIST dataset uses a special binary format, so this function reads the raw bytes and converts them into arrays of numbers the network can work with.

**`main()`** — Ties everything together. Loads the data, creates the network, runs the training loop (forward → backward → update, repeated for each batch and each epoch), tests accuracy, and saves the trained weights.

---

## How to Run It Yourself

### What You Need

- A C compiler (comes pre-installed on most Linux and Mac systems; on Windows you need MinGW or Visual Studio)
- The MNIST dataset (free download, about 55 MB)

### Step 1 — Get the Training Data

Download all 4 files from [yann.lecun.com/exdb/mnist](http://yann.lecun.com/exdb/mnist/) or the [GitHub mirror](https://github.com/cvdfoundation/mnist).

The files you need:
- `train-images-idx3-ubyte.gz` — 60,000 training images
- `train-labels-idx1-ubyte.gz` — labels for the training images
- `t10k-images-idx3-ubyte.gz` — 10,000 test images
- `t10k-labels-idx1-ubyte.gz` — labels for the test images

Unzip all 4 files (on Windows use 7-Zip, on Linux/Mac use `gunzip *.gz`), then put them in a folder called `data` next to your code:

```
your_project/
├── nn.c                            — the neural network
├── draw.c                          — the drawing app (Linux)
├── draw_win.c                      — the drawing app (Windows)
└── data/
    ├── train-images.idx3-ubyte     — 47 MB (training images)
    ├── train-labels.idx1-ubyte     — 60 KB (training labels)
    ├── t10k-images.idx3-ubyte      — 7.8 MB (test images)
    └── t10k-labels.idx1-ubyte      — 10 KB (test labels)
```

### Step 2 — Train the Network

Open a terminal, navigate to your project folder, and run:

```bash
gcc -O2 -o nn nn.c -lm
./nn
```

The first line compiles the code (translates it from human-readable text into a program the computer can run). The second line runs it. You'll see accuracy improving with each epoch. When it finishes (about 2 minutes), it saves the trained weights to a file called `weights.bin`.

**Important:** That's a capital letter O in `-O2`, not the number zero.

### Step 3 — Run the Drawing App

**On Linux:**
```bash
gcc -O2 -o draw draw.c -lX11 -lm
./draw
```

**On Windows (with MinGW):**
```bash
gcc -O2 -o draw.exe draw_win.c -lgdi32 -lm -mwindows
./draw.exe
```

A window pops up with a black canvas. Draw a digit with your mouse, press **G** to have the network guess it, and **C** to clear and try again. Press **Q** to quit.

### What the Compile Commands Mean

| Part | What it does |
|------|-------------|
| `gcc` | The compiler — turns your human-readable code into a program the computer can run |
| `-O2` | Optimize the code so it runs faster (capital letter O, not zero) |
| `-o nn` | Name the output program "nn" |
| `nn.c` | The source code file to compile |
| `-lm` | Include the math library (for functions like square root and exponents) |
| `-lX11` | Include the graphics library (Linux only, for the drawing window) |
| `-lgdi32` | Include the graphics library (Windows only, for the drawing window) |
| `-mwindows` | Make it a graphical app instead of a command-line app (Windows only) |

---

## The Drawing App

After training, the drawing app lets you test the network yourself. It loads the trained weights and runs the same math on your drawing that it used during training.

### Controls

| Action | What it does |
|--------|-------------|
| Left mouse drag | Draw on the canvas |
| Right mouse drag | Erase |
| G key | Guess the digit |
| C key | Clear the canvas |
| Q key or close button | Quit |

### Tips for Best Results

- **Draw in the center** of the canvas, not in a corner
- **Draw big enough** to fill a good portion of the space
- **Draw simply** — the network was trained on basic handwriting, not fancy calligraphy
- **Try different styles** — draw the same digit several ways to see what the network recognizes best and what confuses it

The app shows a probability breakdown for all 10 digits, so you can see not just what the network guessed, but how confident it was and what its second and third choices were.

---

## FAQ

**Q: Is this real AI?**

Yes! Neural networks are one of the core technologies behind modern AI. This is a small one, but it uses the exact same principles (forward propagation, backpropagation, gradient descent) as the massive networks behind things like ChatGPT and image generators. The difference is just scale — this network has 109,000 parameters, while GPT-4 has hundreds of billions.

**Q: Why C? Don't people use Python for AI?**

Most AI research uses Python with libraries like PyTorch or TensorFlow that handle the math for you. Building it in C from scratch means implementing every single operation by hand — there's nowhere to hide and nothing is done for you. It's a much deeper learning experience.

**Q: Why does it only recognize single digits?**

That's a limitation of the training data (MNIST only contains single digits 0–9) and the network size. With more layers, more neurons, and different training data, you could train it to recognize letters, faces, or anything else.

**Q: How is this different from just memorizing the answers?**

Great question. The network is tested on 10,000 images it has never seen during training. If it had just memorized the training images, it would fail on these new ones. The fact that it gets 97%+ on images it's never seen proves it has learned general patterns (what curves, lines, and shapes make up each digit) rather than memorizing specific pictures.

---

## Built By

**Austin** — Procedural Programming, Electrical Engineering

Neural network trained on the [MNIST dataset](https://yann.lecun.com/exdb/mnist/) by Yann LeCun, Corinna Cortes, and Christopher Burges.
