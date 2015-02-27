//  Copyright (c) 2015 Hugo Amiard hugo.amiard@laposte.net
//  This software is provided 'as-is' under the zlib License, see the LICENSE.txt file.
//  This notice and the license may not be removed or altered from any source distribution.

#ifndef MK_GRIDSTORE_H_INCLUDED
#define MK_GRIDSTORE_H_INCLUDED

namespace mk
{
	template <class T_Array>
	class Grided : public T_Array
	{
	public:
		typedef typename T_Array::T T;

	public:
		Grided(size_t x, size_t y, size_t z) : T_Array(), mX(x), mY(y), mZ(z), mSq(x*y) { /*mStore.resize(x*y*z);*/ }

		T* gridAt(size_t x, size_t y, size_t z) { return T_Array::at(x + y*mX + z*mSq); }
		T* safeAt(size_t x, size_t y, size_t z) { if(x > mX || y > mY || z > mZ) return nullptr else return at(x, y, z); }

		size_t x() { return mX; }
		size_t y() { return mY; }
		size_t z() { return mZ; }

		size_t xindex(size_t index) { return index % mY; }
		size_t yindex(size_t index) { return index % mSq / mY; }
		size_t zindex(size_t index) { return index / mSq; }

		T* east(size_t index) { return xindex(index) < xindex(mStore.size() - 1) ? mStore[index + 1] : nullptr; }
		T* west(size_t index) { return xindex(index) > 0 ? mStore[index - 1] : nullptr; }

		T* north(size_t index) { return yindex(index) < yindex(mStore.size() - 1) ? mStore[index + mX] : nullptr; }
		T* south(size_t index) { return yindex(index) > 0 ? mStore[index - mX] : nullptr; }

		T* up(size_t index) { return zindex(index) < zindex(mStore.size() - 1) ? mStore[index + mSq] : nullptr; }
		T* down(size_t index) { return zindex(index) > 0 ? mStore[index - mSq] : nullptr; }

		T* northeast(size_t index) { return mStore[index + 1 + mX]; }
		T* northwest(size_t index) { return mStore[index - 1 + mX]; }
		T* southeast(size_t index) { return mStore[index + 1 - mX]; }
		T* southwest(size_t index) { return mStore[index - 1 - mX]; }

		void iterateFlatNeighbours(size_t x, size_t y, size_t z, size_t d, const std::function<bool(T*)>& callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t xMax = x + d + 1 > mX ? mX : x + d + 1;
			size_t yMax = y + d + 1 > mY ? mY : y + d + 1;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
						if(!callback(this->gridAt(i, j, z)))
							return;
		}

		void iterateNeighbours(size_t x, size_t y, size_t z, size_t d, const std::function<bool(T*)>& callback)
		{
			size_t xMin = x > d ? x - d : 0;
			size_t yMin = y > d ? y - d : 0;
			size_t zMin = z > d ? z - d : 0;
			size_t xMax = x + d + 1 > mX ? mX : x + d + 1;
			size_t yMax = y + d + 1 > mY ? mY : y + d + 1;
			size_t zMax = z + d + 1 > mZ ? mZ : z + d + 1;

			//size_t dsquare = d*d;

			for(size_t i = xMin; i < xMax; ++i)
				for(size_t j = yMin; j < yMax; ++j)
					for(size_t k = zMin; k < zMax; ++k)
						if(!callback(this->gridAt(i, j, k)))
							return;
		}

		void iterateFlatNeighbours(size_t index, size_t dist, const std::function<bool(T*)>& callback)
		{
			size_t x = this->xindex(index);
			size_t y = this->yindex(index);
			size_t z = this->zindex(index);

			return this->iterateFlatNeighbours(x, y, z, dist, callback);
		}

		void iterateNeighbours(size_t index, size_t dist, const std::function<bool(T*)>& callback)
		{
			size_t x = this->xindex(index);
			size_t y = this->yindex(index);
			size_t z = this->zindex(index);

			return this->iterateNeighbours(x, y, z, dist, callback);
		}

		std::vector<T*> neighbours(size_t index, size_t dist)
		{
			std::vector<T*> result;
			this->iterateNeighbours(index, dist, [&result](T* obj){ result.push_back(obj); return true; });
			result.erase(std::remove(result.begin(), result.end(), this->at(index)), result.end());
			return result;
		}

		std::vector<T*> flatNeighbours(size_t index, size_t dist)
		{
			std::vector<T*> result;
			this->iterateFlatNeighbours(index, dist, [&result](T* obj){ result.push_back(obj); return true; });
			result.erase(std::remove(result.begin(), result.end(), this->at(index)), result.end());
			return result;
		}

	protected:
		size_t mX, mY, mZ;
		size_t mSq;
	};
}

#endif // MK_GRIDSTORE_H_INCLUDED
