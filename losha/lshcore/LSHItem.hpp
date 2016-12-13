/*
 * Copyright 2016 husky Team
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once
#include <string>
#include <utility>
#include <vector>

#include "base/log.hpp"
#include "core/engine.hpp"

#include "DenseVector.hpp"
#include "LSHFactory.hpp"

namespace husky {
namespace losha {

template<typename ItemIdType,
         typename ItemElementType,
         typename QueryMsg = DenseVector<ItemIdType, ItemElementType>,
         typename AnswerMsg = std::pair<ItemIdType, float> >
class LSHItem: public DenseVector<ItemIdType, ItemElementType> {
public:

    static thread_local std::vector< std::pair<ItemIdType, AnswerMsg> > item_msg_buffer;
    std::vector< QueryMsg > query_msg_buffer;

    // require by Husky object
    explicit LSHItem(const typename LSHItem::KeyT& id) : DenseVector<ItemIdType, ItemElementType>(id) {};

    inline void sendToQuery(const ItemIdType& qId, const AnswerMsg& msg) {
        item_msg_buffer.push_back(std::make_pair(qId, msg));
    }

    const std::vector<QueryMsg>& getQueryMsg() {
        return query_msg_buffer;
    }

    virtual void answer(
        LSHFactory<ItemIdType, ItemElementType>& factory,
        const vector<QueryMsg>& inMsg) {
    }
};

template<typename ItemIdType,
         typename ItemElementType,
         typename QueryMsg,
         typename AnswerMsg >
thread_local std::vector<std::pair<ItemIdType, AnswerMsg>> LSHItem<ItemIdType,
    ItemElementType,
    QueryMsg,
    AnswerMsg>::item_msg_buffer;

// should be deprecated
// template<typename ItemIdType,
//          typename ItemElementType,
//          typename QueryMsg,
//          typename AnswerMsg >
// std::string LSHItem<ItemIdType,
//     ItemElementType,
//     QueryMsg,
//     AnswerMsg>::default_list_name = "item_list";

} // namespace losha
} // namespace husky
