import React, { useLayoutEffect } from 'react'
import { StyleSheet, View, Text } from 'react-native'
import { Avatar } from 'react-native-elements';
import { db } from '../firebase';
import { auth } from '../firebase';
const ChatScreen = ( {navigation, route } ) => {
    useLayoutEffect(() => {
        navigation.setOptions({
            headerBackTitleVisitable: false,
            headerStyle: { backgroundColor: '#2089DC'},
            headerTitle: () => (
                <View
                    style={{
                        flexDirection: "row",
                        alignItems: "center"
                    }}
                >
                    <Avatar
                        rounded
                        source={{
                            uri: auth?.currentUser?.photoURL
                        }}
                    />
                    <Text
                        style={{
                            fontSize: 20,
                            fontWeight: "bold",
                            color: "white",
                            marginLeft: 15
                        }}
                    >{route.params.chatName}</Text>
                </View>
            )
        });
    }, [navigation]);
    return (
        <View>
            <Text>{route.params.chatName}</Text>
        </View>
    )
}

export default ChatScreen

const styles = StyleSheet.create({})
