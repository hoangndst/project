import React from 'react'
import { StyleSheet, Text, View } from 'react-native'
import { ListItem, Avatar } from 'react-native-elements'

const CustomListItem = () => {
    return (
        <ListItem>
            <Avatar
                rounded
                source={{
                    uri:
                        "https://upload.wikimedia.org/wikipedia/commons/7/7c/Profile_avatar_placeholder_large.png",
                }}
            />
        </ListItem>
    )
}

export default CustomListItem

const styles = StyleSheet.create({})
