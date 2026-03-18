#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>


// Network size
#define INPUT   784  // We did 784 because for 1 input per pixel per image
#define HIDDEN  128  // adding a hidden layer would better help with a higher accuracy
#define OUTPUT  10   // this is what the NN is spitting out 0-9

// Weights and biases
double W1[HIDDEN][INPUT];
double b1[HIDDEN];
double W2[OUTPUT][HIDDEN];
double b2[OUTPUT];

// Activations (both pre and post)
double z1[HIDDEN];
double a1[HIDDEN];
double z2[OUTPUT];
double a2[OUTPUT];

// Gradients (the 'how fast' a model learns..)
double dW1[HIDDEN][INPUT];
double db1[HIDDEN];
double dW2[OUTPUT][HIDDEN];
double db2[OUTPUT];

// Data storage (putting all the images into their own array)
double train_images[60000][INPUT];
int    train_labels[60000];
double test_images[10000][INPUT];
int    test_labels[10000];

// random initialization
// filling the weights of the neurons with a slighly random value to get the model kicked off
// the slightyl random is because we dont want the weights to explode or change rather drastically
// so we used sqrt(2) / fan_in_value to start off the weights

void init_weights(void) {
    double scale1 = sqrt(2.0 / INPUT);
    for (int i = 0; i < HIDDEN; i++) {
        for (int j = 0; j < INPUT; j++) {
            W1[i][j] = ((double)rand() / RAND_MAX - 0.5) * 2.0 * scale1;
        }
        b1[i] = 0.0;
    }

    double scale2 = sqrt(2.0 / HIDDEN);
    for (int i = 0; i < OUTPUT; i++) {
        for (int j = 0; j < HIDDEN; j++) {
            W2[i][j] = ((double)rand() / RAND_MAX - 0.5) * 2.0 * scale2;
        }
        b2[i] = 0.0;
    }
}

// forward pass - feed one image through the network at at time
//
// step 1 is to calcualte the only hidden layer
//      hidden = ReLU(W1 * input + b1)
// step 2 is calcualte the output layer  
//      output = softmax(W2 * hidden + b2)
// 
void forward(double *input) {
    /* Hidden layer: z1 = W1*input + b1, then ReLU */
    for (int i = 0; i < HIDDEN; i++) {
        z1[i] = b1[i];
        for (int j = 0; j < INPUT; j++) {
            z1[i] += W1[i][j] * input[j];
        }
        a1[i] = z1[i] > 0.0 ? z1[i] : 0.0;  /* ReLU */
    }

    /* Output layer: z2 = W2*hidden + b2, then softmax */
    double max_z = -1e30;
    for (int i = 0; i < OUTPUT; i++) {
        z2[i] = b2[i];
        for (int j = 0; j < HIDDEN; j++) {
            z2[i] += W2[i][j] * a1[j];
        }
        if (z2[i] > max_z) max_z = z2[i];
    }

    /* Softmax with numerical stability (subtract max first) */
    double sum = 0.0;
    for (int i = 0; i < OUTPUT; i++) {
        a2[i] = exp(z2[i] - max_z);
        sum += a2[i];
    }
    for (int i = 0; i < OUTPUT; i++) {
        a2[i] /= sum;
    }
}


// backward pass. this computes the gradients for an image.
// Starting from the loss, work backwards using the chain rule
// to figure out how much each weight contributed to the error.
 
void backward(double *input, int label) {
    // output layer gradient
    double dz2[OUTPUT];
    for (int i = 0; i < OUTPUT; i++) {
        dz2[i] = a2[i] - (i == label ? 1.0 : 0.0);
    }

    // gradients for weight 2 and bias 2
    for (int i = 0; i < OUTPUT; i++) {
        for (int j = 0; j < HIDDEN; j++) {
            dW2[i][j] += dz2[i] * a1[j];
        }
        db2[i] += dz2[i];
    }

    // back propagation through the hidden layer
    double dz1[HIDDEN];
    for (int i = 0; i < HIDDEN; i++) {
        double da = 0.0;
        for (int k = 0; k < OUTPUT; k++) {
            da += W2[k][i] * dz2[k];
        }
        dz1[i] = da * (z1[i] > 0.0 ? 1.0 : 0.0);  // ReLU
    }

    // gradients for weight1 and bias1
    for (int i = 0; i < HIDDEN; i++) {
        for (int j = 0; j < INPUT; j++) {
            dW1[i][j] += dz1[i] * input[j];
        }
        db1[i] += dz1[i];
    }
}

// apply gradient descent
void update(double lr, int batch_size) {
    double scale = lr / batch_size;

    for (int i = 0; i < HIDDEN; i++) {
        for (int j = 0; j < INPUT; j++) {
            W1[i][j] -= scale * dW1[i][j];
            dW1[i][j] = 0.0;
        }
        b1[i] -= scale * db1[i];
        db1[i] = 0.0;
    }

    for (int i = 0; i < OUTPUT; i++) {
        for (int j = 0; j < HIDDEN; j++) {
            W2[i][j] -= scale * dW2[i][j];
            dW2[i][j] = 0.0;
        }
        b2[i] -= scale * db2[i];
        db2[i] = 0.0;
    }
}


// MNIST loader — read the binary IDX files.
// These files store integers in big-endian byte order.

int read_int(FILE *f) {
    unsigned char b[4];
    if (fread(b, 1, 4, f) != 4) return 0;
    return (b[0] << 24) | (b[1] << 16) | (b[2] << 8) | b[3];
}

int load_mnist(const char *img_path, const char *lbl_path, double images[][INPUT], int *labels, int max_count){
    
    FILE *fimg = fopen(img_path, "rb");
    FILE *flbl = fopen(lbl_path, "rb");
    if (!fimg || !flbl) {
        printf("Error: can't open %s or %s\n", img_path, lbl_path);
        return 0;}

    read_int(fimg);
    int count = read_int(fimg);
    read_int(fimg);
    read_int(fimg);

    read_int(flbl);
    read_int(flbl);

    if (count > max_count) count = max_count;

    for (int i = 0; i < count; i++) {
        unsigned char pixels[INPUT];
        if (fread(pixels, 1, INPUT, fimg) != INPUT) break;
        for (int j = 0; j < INPUT; j++) {
            images[i][j] = pixels[j] / 255.0;
        }
        unsigned char lbl;
        if (fread(&lbl, 1, 1, flbl) != 1) break;
        labels[i] = lbl;
    }

    fclose(fimg);
    fclose(flbl);
    printf("  Loaded %d samples from %s\n", count, img_path);
    return count;
}


// the main execution — trains and evaluates.
int main(void) {
    srand((unsigned)time(NULL));

    printf("Loading data...\n");
    int n_train = load_mnist("data/train-images.idx3-ubyte", "data/train-labels.idx1-ubyte", train_images, train_labels, 60000);
    int n_test  = load_mnist("data/t10k-images.idx3-ubyte", "data/t10k-labels.idx1-ubyte", test_images, test_labels, 10000);
    
    if (n_train == 0 || n_test == 0) {
        printf("Put MNIST files in data/ folder.\n");
        return 1;
    }

    printf("\nInitializing weights...\n");
    init_weights();

    // Training
    // these variables are the control panel
    // we have learning rate, batch size, and epochs

    double lr = 0.01; // how fast a neuron can change
    int batch_size = 8; // how many images the training bot has to take in before changing weights
    int epochs = 5; // the number of times the network has to run through all the training data and is then shuffled and starts again

    // so in total... 
    // the NN has is being trained against
    // 60000 images * 10 rounds / 32 images per batch
    // = 18750 weight adjustments per neuron!
    // that is a grand total of (128 + 10) neurons * 18750 weight adjustments = 2,587,500 weight changes in total

    printf("n_test: %d\n", n_test);
    printf("n_train: %d\n", n_train);
    printf("Training: %d -> %d -> %d\n\n", INPUT, HIDDEN, OUTPUT);
    
    // runs through epoch iterations
    for (int epoch = 0; epoch < epochs; epoch++) {
        for (int i = 0; i < n_train; i++) {
            forward(train_images[i]);
            backward(train_images[i], train_labels[i]);

            if ((i + 1) % batch_size == 0) {
                update(lr, batch_size);
            }
        }

        // Test accuracy
        int correct = 0;
        for (int i = 0; i < n_test; i++) {
            forward(test_images[i]);
            int pred = 0;
            for (int k = 1; k < OUTPUT; k++) {
                if (a2[k] > a2[pred]) pred = k;
            }
            if (pred == test_labels[i]) 
            correct++;}
        // displays the epoch after it done with each
        printf("Epoch %2d | Accuracy: %.2f%%\n", epoch + 1, 100.0 * correct / n_test);
    }
    // saves the weights so the drawing windows can be calibrated
    FILE *f = fopen("weights.bin", "wb");
    if (f) {
        fwrite(W1, sizeof(double), HIDDEN * INPUT, f);
        fwrite(b1, sizeof(double), HIDDEN, f);
        fwrite(W2, sizeof(double), OUTPUT * HIDDEN, f);
        fwrite(b2, sizeof(double), OUTPUT, f);
        fclose(f);
        printf("\nWeights saved to weights.bin\n");
    }

    printf("Done.\n");
    printf("");
    return 0;
}

