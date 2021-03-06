/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_basegfx.hxx"
#include <osl/diagnose.h>
#include <basegfx/polygon/b3dpolypolygon.hxx>
#include <basegfx/polygon/b3dpolygon.hxx>
#include <rtl/instance.hxx>
#include <basegfx/matrix/b2dhommatrix.hxx>
#include <basegfx/matrix/b3dhommatrix.hxx>
#include <functional>
#include <vector>
#include <algorithm>

//////////////////////////////////////////////////////////////////////////////

class ImplB3DPolyPolygon
{
	typedef ::std::vector< ::basegfx::B3DPolygon >	PolygonVector;

	PolygonVector									maPolygons;

public:
	ImplB3DPolyPolygon() : maPolygons()
    {
    }

	ImplB3DPolyPolygon(const ::basegfx::B3DPolygon& rToBeCopied) :
        maPolygons(1,rToBeCopied)
	{
	}

	bool operator==(const ImplB3DPolyPolygon& rPolygonList) const
	{
		// same polygon count?
		if(maPolygons.size() != rPolygonList.maPolygons.size())
			return false;

		// compare polygon content
		if(maPolygons != rPolygonList.maPolygons)
			return false;

		return true;
	}

	const ::basegfx::B3DPolygon& getB3DPolygon(sal_uInt32 nIndex) const
	{
		return maPolygons[nIndex];
	}

	void setB3DPolygon(sal_uInt32 nIndex, const ::basegfx::B3DPolygon& rPolygon)
	{
		maPolygons[nIndex] = rPolygon;
	}

	void insert(sal_uInt32 nIndex, const ::basegfx::B3DPolygon& rPolygon, sal_uInt32 nCount)
	{
		if(nCount)
		{
			// add nCount copies of rPolygon
			PolygonVector::iterator aIndex(maPolygons.begin());
			aIndex += nIndex;
			maPolygons.insert(aIndex, nCount, rPolygon);
		}
	}

	void insert(sal_uInt32 nIndex, const ::basegfx::B3DPolyPolygon& rPolyPolygon)
	{
		const sal_uInt32 nCount = rPolyPolygon.count();

		if(nCount)
		{
			// add nCount polygons from rPolyPolygon
			maPolygons.reserve(maPolygons.size() + nCount);
			PolygonVector::iterator aIndex(maPolygons.begin());
			aIndex += nIndex;

			for(sal_uInt32 a(0L); a < nCount; a++)
			{
				maPolygons.insert(aIndex, rPolyPolygon.getB3DPolygon(a));
				aIndex++;
			}
		}
	}

	void remove(sal_uInt32 nIndex, sal_uInt32 nCount)
	{
		if(nCount)
		{
			// remove polygon data
			PolygonVector::iterator aStart(maPolygons.begin());
			aStart += nIndex;
			const PolygonVector::iterator aEnd(aStart + nCount);

			maPolygons.erase(aStart, aEnd);
		}
	}

	sal_uInt32 count() const
	{
		return maPolygons.size();
	}

	void setClosed(bool bNew)
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].setClosed(bNew);
		}
	}

	void flip()
	{
        std::for_each( maPolygons.begin(),
                       maPolygons.end(),
                       std::mem_fun_ref( &::basegfx::B3DPolygon::flip ));
	}

	void removeDoublePoints()
	{
        std::for_each( maPolygons.begin(),
                       maPolygons.end(),
                       std::mem_fun_ref( &::basegfx::B3DPolygon::removeDoublePoints ));
	}

	void transform(const ::basegfx::B3DHomMatrix& rMatrix)
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].transform(rMatrix);
		}
	}

	void clearBColors()
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].clearBColors();
		}
	}

	void transformNormals(const ::basegfx::B3DHomMatrix& rMatrix)
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].transformNormals(rMatrix);
		}
	}

	void clearNormals()
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].clearNormals();
		}
	}

	void transformTextureCoordiantes(const ::basegfx::B2DHomMatrix& rMatrix)
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].transformTextureCoordiantes(rMatrix);
		}
	}

	void clearTextureCoordinates()
	{
		for(sal_uInt32 a(0L); a < maPolygons.size(); a++)
		{
			maPolygons[a].clearTextureCoordinates();
		}
	}

    void makeUnique()
    {
        std::for_each( maPolygons.begin(),
                       maPolygons.end(),
                       std::mem_fun_ref( &::basegfx::B3DPolygon::makeUnique ));
    }
};

//////////////////////////////////////////////////////////////////////////////

namespace basegfx
{
    namespace { struct DefaultPolyPolygon : public rtl::Static<B3DPolyPolygon::ImplType, 
                                                               DefaultPolyPolygon> {}; }

	B3DPolyPolygon::B3DPolyPolygon() :
        mpPolyPolygon(DefaultPolyPolygon::get())
	{
	}

	B3DPolyPolygon::B3DPolyPolygon(const B3DPolyPolygon& rPolyPolygon) :
        mpPolyPolygon(rPolyPolygon.mpPolyPolygon)
	{
	}

	B3DPolyPolygon::B3DPolyPolygon(const B3DPolygon& rPolygon) :
        mpPolyPolygon( ImplB3DPolyPolygon(rPolygon) )
	{
	}

	B3DPolyPolygon::~B3DPolyPolygon()
	{
	}

	B3DPolyPolygon& B3DPolyPolygon::operator=(const B3DPolyPolygon& rPolyPolygon)
	{
		mpPolyPolygon = rPolyPolygon.mpPolyPolygon;
		return *this;
	}

    void B3DPolyPolygon::makeUnique()
    {
        mpPolyPolygon.make_unique();
        mpPolyPolygon->makeUnique();
    }

	bool B3DPolyPolygon::operator==(const B3DPolyPolygon& rPolyPolygon) const
	{
		if(mpPolyPolygon.same_object(rPolyPolygon.mpPolyPolygon))
			return true;

		return ((*mpPolyPolygon) == (*rPolyPolygon.mpPolyPolygon));
	}

	bool B3DPolyPolygon::operator!=(const B3DPolyPolygon& rPolyPolygon) const
	{
        return !(*this == rPolyPolygon);
	}

	sal_uInt32 B3DPolyPolygon::count() const
	{
		return mpPolyPolygon->count();
	}

	B3DPolygon B3DPolyPolygon::getB3DPolygon(sal_uInt32 nIndex) const
	{
		OSL_ENSURE(nIndex < mpPolyPolygon->count(), "B3DPolyPolygon access outside range (!)");
		
		return mpPolyPolygon->getB3DPolygon(nIndex);
	}

	void B3DPolyPolygon::setB3DPolygon(sal_uInt32 nIndex, const B3DPolygon& rPolygon)
	{
		OSL_ENSURE(nIndex < mpPolyPolygon->count(), "B3DPolyPolygon access outside range (!)");

		if(getB3DPolygon(nIndex) != rPolygon)
			mpPolyPolygon->setB3DPolygon(nIndex, rPolygon);
	}

	bool B3DPolyPolygon::areBColorsUsed() const
	{
		for(sal_uInt32 a(0L); a < mpPolyPolygon->count(); a++)
		{
			if((mpPolyPolygon->getB3DPolygon(a)).areBColorsUsed())
			{
				return true;
			}
		}

		return false;
	}

	void B3DPolyPolygon::clearBColors()
	{
		if(areBColorsUsed())
			mpPolyPolygon->clearBColors();
	}

	void B3DPolyPolygon::transformNormals(const B3DHomMatrix& rMatrix)
	{
		if(!rMatrix.isIdentity())
			mpPolyPolygon->transformNormals(rMatrix);
	}

	bool B3DPolyPolygon::areNormalsUsed() const
	{
		for(sal_uInt32 a(0L); a < mpPolyPolygon->count(); a++)
		{
			if((mpPolyPolygon->getB3DPolygon(a)).areNormalsUsed())
			{
				return true;
			}
		}

		return false;
	}

	void B3DPolyPolygon::clearNormals()
	{
		if(areNormalsUsed())
			mpPolyPolygon->clearNormals();
	}

	void B3DPolyPolygon::transformTextureCoordiantes(const B2DHomMatrix& rMatrix)
	{
		if(!rMatrix.isIdentity())
			mpPolyPolygon->transformTextureCoordiantes(rMatrix);
	}

	bool B3DPolyPolygon::areTextureCoordinatesUsed() const
	{
		for(sal_uInt32 a(0L); a < mpPolyPolygon->count(); a++)
		{
			if((mpPolyPolygon->getB3DPolygon(a)).areTextureCoordinatesUsed())
			{
				return true;
			}
		}

		return false;
	}

	void B3DPolyPolygon::clearTextureCoordinates()
	{
		if(areTextureCoordinatesUsed())
			mpPolyPolygon->clearTextureCoordinates();
	}

	void B3DPolyPolygon::insert(sal_uInt32 nIndex, const B3DPolygon& rPolygon, sal_uInt32 nCount)
	{
		OSL_ENSURE(nIndex <= mpPolyPolygon->count(), "B3DPolyPolygon Insert outside range (!)");
		
		if(nCount)
			mpPolyPolygon->insert(nIndex, rPolygon, nCount);
	}

	void B3DPolyPolygon::append(const B3DPolygon& rPolygon, sal_uInt32 nCount)
	{
		if(nCount)
			mpPolyPolygon->insert(mpPolyPolygon->count(), rPolygon, nCount);
	}

	void B3DPolyPolygon::insert(sal_uInt32 nIndex, const B3DPolyPolygon& rPolyPolygon)
	{
		OSL_ENSURE(nIndex <= mpPolyPolygon->count(), "B3DPolyPolygon Insert outside range (!)");
		
		if(rPolyPolygon.count())
			mpPolyPolygon->insert(nIndex, rPolyPolygon);
	}

	void B3DPolyPolygon::append(const B3DPolyPolygon& rPolyPolygon)
	{
		if(rPolyPolygon.count())
			mpPolyPolygon->insert(mpPolyPolygon->count(), rPolyPolygon);
	}

	void B3DPolyPolygon::remove(sal_uInt32 nIndex, sal_uInt32 nCount)
	{
		OSL_ENSURE(nIndex + nCount <= mpPolyPolygon->count(), "B3DPolyPolygon Remove outside range (!)");
		
		if(nCount)
			mpPolyPolygon->remove(nIndex, nCount);
	}
	
	void B3DPolyPolygon::clear()
	{
		mpPolyPolygon = DefaultPolyPolygon::get();
	}

	bool B3DPolyPolygon::isClosed() const
	{
		bool bRetval(true);

		// PolyPOlygon is closed when all contained Polygons are closed or
		// no Polygon exists.
		for(sal_uInt32 a(0L); bRetval && a < mpPolyPolygon->count(); a++)
		{
			if(!(mpPolyPolygon->getB3DPolygon(a)).isClosed())
			{
				bRetval = false;
			}
		}

		return bRetval;
	}

	void B3DPolyPolygon::setClosed(bool bNew)
	{
		if(bNew != isClosed())
			mpPolyPolygon->setClosed(bNew);
	}

	void B3DPolyPolygon::flip()
	{
		mpPolyPolygon->flip();
	}

	bool B3DPolyPolygon::hasDoublePoints() const
	{
		bool bRetval(false);

		for(sal_uInt32 a(0L); !bRetval && a < mpPolyPolygon->count(); a++)
		{
			if((mpPolyPolygon->getB3DPolygon(a)).hasDoublePoints())
			{
				bRetval = true;
			}
		}

		return bRetval;
	}

	void B3DPolyPolygon::removeDoublePoints()
	{
		if(hasDoublePoints())
			mpPolyPolygon->removeDoublePoints();
	}

	void B3DPolyPolygon::transform(const B3DHomMatrix& rMatrix)
	{
		if(mpPolyPolygon->count() && !rMatrix.isIdentity())
		{
			mpPolyPolygon->transform(rMatrix);
		}
	}
} // end of namespace basegfx

// eof
