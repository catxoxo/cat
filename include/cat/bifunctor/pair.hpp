/******************************************************************************
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014-15 Nicola Bonelli <nicola@pfq.io>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 ******************************************************************************/

#pragma once

#include <tuple>
#include <cat/bifunctor/bifunctor.hpp>

namespace cat
{
    // std::pair is a functor:
    //

    template <> struct is_bifunctor<std::pair> : std::true_type { };

    // std::pair instance:
    //

    template <typename F, typename G, typename A, typename B>
    struct BifunctorInstance<std::pair, F, G, A, B> : Bifunctor<std::pair>::Class<F, G, A, B>
    {
        using C = decltype(std::declval<F>()(std::declval<A>()));
        using D = decltype(std::declval<G>()(std::declval<B>()));

        std::pair<C, D>
        bimap(F f, G g, std::pair<A, B> const &xs) final
        {
            return std::make_pair(f(xs.first), g(xs.second));
        }

        std::pair<C, B>
        first(F f, std::pair<A, B> const &xs) final
        {
            return std::make_pair(f(xs.first), xs.second);
        }

        std::pair<A, D>
        second(G g, std::pair<A, B> const &xs) final
        {
            return std::make_pair(xs.first, g(xs.second));
        }
    };

} // namespace cat

