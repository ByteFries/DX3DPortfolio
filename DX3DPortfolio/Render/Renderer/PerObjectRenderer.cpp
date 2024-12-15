#include "framework.h"
#include "PerObjectRenderer.h"

PerObjectRenderer::PerObjectRenderer()
{
}

PerObjectRenderer::~PerObjectRenderer()
{
}


void PerObjectRenderer::Draw(int indexCount)
{
	DC->DrawIndexed(indexCount,0,0);
}