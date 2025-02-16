#include "Scene.h"

USING(Engine)

Scene::Scene(_uint nSceneIndex)
	: Composite()
	, m_nScene(nSceneIndex)
{
}

Scene* Scene::Create(_uint nSceneIndex)
{
	return new Scene(nSceneIndex);
}

void Scene::Free()
{
	__super::Free();
}
