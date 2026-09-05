#include "Render.h"
#include <iostream>

using namespace std;

int main () {
	Render r(1800,1200,"Test");
	Render::Scene s(string("scene1"),r);

	Render::Shader sh("vert.glsl","frag.glsl",r);
	
	Render::Mesh rect(r);
	rect.vertexComp(vector<unsigned int>{2,3}); // 2d position, color
	rect.vertices(vector<float>{
		-.5f,-.5f, 	1,0,0,
		-.5f, .5f, 	0,1,0,
		 .5f, .5f, 	0,0,1,
		 .5f,-.5f, 	1,1,1
	});
	rect.indices(vector<unsigned int>{
		0,1,2,
		0,2,3
	});
	rect.updateBuffer();

	Render::TickFunc t(r);
	t.permanent.store(true);
	t.preferedPriority.store(1);
	t.f = [&]() {
		if (glfwGetKey(r.window,GLFW_KEY_ESCAPE)) r.running = false;
		if (!rect.isLoaded()) return;

		glUseProgram(sh.ID);

		glBindVertexArray(rect.VAO);
		glDrawElements(GL_TRIANGLES, rect.totalIndices(), GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	};

	s.addAsset(&sh);
	s.addAsset(&rect);
	s.addAsset(&t);

	r.setScene("scene1");

	if (r.Thread->joinable()) {
		r.Thread->join();
	}
	return 0;
}