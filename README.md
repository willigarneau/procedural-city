 <h1 align="center">Procedural City Generation</h1> 
  <p align="center">
  <img src="https://img.shields.io/badge/License-MIT-blue.svg"><br>
  <img src="https://api.codacy.com/project/badge/Grade/e28ff30817f945c4b782a383e2711f8d"/></a><br>
  Made with OpenGL, FreeGlut, Glew, SOIL, GLM and shaders.
  </p>

## Showcase

Here's an **example** of the camera and the rendering with OpenGL. 

<p align="center">
  <img src="https://user-images.githubusercontent.com/33030290/48488025-d6189200-e7ed-11e8-9821-491b4853257c.gif")><br>
</p>

## Controls

<center>
 
| Input   |  Description |
|:----------:|:------:|
| 'w' | Move forward in the environment |
| 'a' | Move backward in the environment |
| 's' | Move left in the environment |
| 'd' | Move right in the environment |
| Mouse Move | Look around you with Euler Angles |
| Mouse Wheel | Zoom in/Zoom out |
| 'r' | Re-generate the building sizes and textures |
| 'o' | Move up in the environment |
| 'p' | Move down in the environment |

</center>

Here's an example of how the program reacts to a **re-generation** of the buildings. I store the x, y, z and texture identifier in vectors, so the randomization is just made by clearing them and regenerate random numbers in it. It is draw at each movement by the camera, which makes the random very fluid. :

```c++
if (!hasStarted) {
		for (int i = 0; i < nbBuildings * nbBuildings; i++) {
			float randomX = ((2.0f - 0.25f) * ((float)rand() / RAND_MAX)) + 0.25f;
			float randomY = ((4.5f - 0.25f) * ((float)rand() / RAND_MAX)) + 0.25f;
			float randomZ = ((2.25f - 0.75f) * ((float)rand() / RAND_MAX)) + 0.75f;
			float randomTex = rand() % 5;
			_x.push_back(randomX);
			_y.push_back(randomY);
			_z.push_back(randomZ);
			_texture.push_back(randomTex);
		}
		hasStarted = true;
	}
```

**And here's the rendering of the random method ->**

<p align="center">
  <img src="https://user-images.githubusercontent.com/33030290/48489759-c13dfd80-e7f1-11e8-9770-0d6b82e70d58.gif")><br>
</p>

## Summary
First, what is **procedural generation**?

**From [Wikipedia](https://en.wikipedia.org/wiki/Procedural_generation) :** In computing, **procedural generation** is a method of creating data *algorithmically* as opposed to manually. In computer graphics, it is also called **random generation** and is commonly used to create textures and 3D models. In video games, it is used to *automatically create large amounts of content in a game*. Advantages of procedural generation include smaller file sizes, larger amounts of content, and randomness for less predictable gameplay.

*For the purpose of my project*, the goal was rather to find a way to generate buildings randomly in a small space.

Initially, it was a task I had received in my computer graphics course. Usually, in these cases, I immerse myself in the Github projects to get inspired by the kind of program structure I will need. However, I did not find anything concrete with the librairies I used.

Users used a lot more **GLFW than FreeGlut**. The few people who used the same tools as me had programs far too complicated for anything.

So I decided to start from 0 and create a quick and easy way to *randomly generate a city with buildings of different size and with different textures*, all using shaders.

I did not complicate my life, I created a single *VAO* to which I was going to apply transformations to avoid going into an overly complex generation structure.

#### Since there might still be some problems in my implementation, so please feel free to give me any advice!

So here is the result of what I made. I hope you will have fun with it!

**Note :** You can choose the amount of buildings to generate just by changing the **nbBuildings** property.

---

## Prerequisites

Ensure you have following installed:

  - [Visual Studio Community 2017](https://visualstudio.microsoft.com/downloads/)

## Compile and run

As simple as:

```c++
1. Open the project in VS.
2. Execute the project.
3. Have fun !
```

or by debugging the whole program in **Visual Studio Entreprise**

---

## My build environment

In case you face difficulty building on your own machine, 
following is the specifications of my environment which may be 
helpful for you to spot the difference to yours.

<b>OS</b>

```text
Windows 10 2018
```

<b>Configuration</b>

```text
CPU -> Intel Core i7 3960X
RAM -> 16Gb DDR3 1600Hz
GPU -> NVIDIA GEFORCE 1080 Founder's edition
STORAGE -> 1To SSD
POWER SUPPLY -> 750W GOLD
MOTHERBOARD -> Aurora R4 ALX System Motherboard 7JNH0 07JNH0
```

<b>OpenGL</b>

You can find the last version of OpenGL by following this [link](https://www.opengl.org/)

<b>FreeGlut</b>

All informations about this library can be found on http://freeglut.sourceforge.net/.

<b>Glew</b>

All informations about this library can be found on http://glew.sourceforge.net/

<b>GLM</b>

All informations about this library can be found on https://glm.g-truc.net/0.9.9/index.html

<b>SOIL</b>

All informations about this library can be found on https://www.khronos.org/opengl/wiki/Image_Libraries

---

# Licence

None for this project, it's for the purpose of a class
